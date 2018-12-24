#include "FormExpressionCommand.h"
#include "Utils.h"
#include "Number.h"
#include "BinaryExpressions.h"

/*
FormExpressionCommand: constructor
*/
FormExpressionCommand::FormExpressionCommand(map<string, double> &symbolTable) {
    // hold a reference to the main symbol table of the program
    this->symbolTable = &symbolTable;
}

/*
in charge of evaluating the expression it receives. it does this by a series of actions,
including split into the tokens, conversion to Postfix format, and calculating the numerical
value of the expression
*/
void FormExpressionCommand::doCommand(vector<string> args) {
    //throw exception if an empty expression was given
    if ((args[0].size() == 0)||(args[0] == " ")) {
        throw logic_error("invalid expression");
    }
    this->infix = args[0];
    //replace variables names with their values
    evaluateVars();
    //if only a sinlge character was given
    if (isSignelNumber()) {
        //evaluate its value and hold result
        e = new Number(stod(infix));
        result = to_string(e->calculate());
        //if the expression is composed of more then one character
    } else {
        //split to tokens
        toTokens();
        //rewrite the way negative numbers are written
        rewriteNegativeExp();
        //convert from infix to postfix
        string postfix = convertToPostfix();
        //convert from postfix to numerical expression
        e = fromPostfixToExpr(postfix);
        //hold the string of the result
        result = to_string(e->calculate());
    }
}

/*
in charge of replacing variables names with their values in the given expression, in case where given
*/
void FormExpressionCommand::evaluateVars() {
    map<string,double>::iterator iter;
    //for each variable in the symbol table
    for (iter = symbolTable->begin(); iter != symbolTable->end(); ++iter) {
        string var = iter->first;
        string value = to_string(iter->second);
        //replace all its appearances in the expression
        while (infix.find(var) != string::npos) {
            int pos = infix.find(var);
            infix.replace(pos, var.size(), value);
        }
    }
}

/*
returns if the given expression is a single number
*/
bool FormExpressionCommand::isSignelNumber() {
    //for each char
    for (int i = 0; i < infix.size(); i++) {
        //if is operator or parenthesis, then the expression is not a single number
        if ((infix[i] == '+')||(infix[i] == '-')||(infix[i] == '*')||(infix[i] == '/')||
        (infix[i] == '(')||(infix[i] == ')')) {
            return false;
        }
    }
    return true;
}

/*
returns the precedence of the given operator
*/
int FormExpressionCommand::precedence(string oper) {
    if ((oper == "+")||(oper == "-")) {
        return 1;
    } else if ((oper == "*")||(oper == "/")) {
        return 2;
    }
}

/*
returns if the given char is a digit
*/
bool FormExpressionCommand::isDigit(char c) {
    return ((c == '0')||(c == '1')||(c == '2')||(c == '3')||(c == '4')||(c == '5')||(c == '6')||
    (c == '7')||(c == '8')||(c == '9'));
}

/*
returns if the given infix token is a number
*/
bool FormExpressionCommand::isNumber(string token) {
    //if the first char is minus
    if (token[0] == '-') {
        //if the token size > 1, then the minus char is a part of a negative number
        return (token.size() >= 2);
    }
    //else, its is a number only if the first character is a digit
    return isDigit(token[0]);
}

/*
returns if the given infix token is an operator
*/
bool FormExpressionCommand::isOperator(string token) {
    return ((token == "+")||(token == "-")||(token == "*")||(token == "/"));
}

/*
separate the given expression to tokens, with spaces in between
*/
void FormExpressionCommand::toTokens() {
    //throw exception in case of invalid use of 2 operators in a row
    for (int i = 0; i < infix.size() - 1; i++) {
        if ((infix[i] == '+')&&(infix[i + 1] == '+')) {
            throw logic_error("invalid expression");
        } else if ((infix[i] == '-')&&(infix[i + 1] == '+')) {
            throw logic_error("invalid expression");
        } else if ((infix[i] == '+')&&(infix[i + 1] == '+')) {
            throw logic_error("invalid expression");
        } else if ((infix[i] == '*')&&(infix[i + 1] == '/')) {
            throw logic_error("invalid expression");
        } else if ((infix[i] == '/')&&(infix[i + 1] == '*')) {
            throw logic_error("invalid expression");
        } else if ((infix[i] == '(')&&(infix[i + 1] == ')')) {
            throw logic_error("invalid expression");
        } else if ((infix[i] == ')')&&(infix[i + 1] == '(')) {
            throw logic_error("invalid expression");
        }
    }
    string result = "";
    //for each character in the expression
    for (int i = 0; i < infix.size(); i++) {
        //if is operator or a parenthesis put space in between
        if ((infix[i] == '+')||(infix[i] == '-')||(infix[i] == '*')||(infix[i] == '/')||
        (infix[i] == '(')||(infix[i] == ')')) {
            result += infix[i];
            result += " ";
            //ignore spaces
        } else if (infix[i] == ' ') {
            continue;
            //if is digit
        } else if (isDigit(infix[i])) {
            //if is the last char in the expression
            if (i + 1 >= infix.size()) {
                result += infix[i];
                //else, put space in between or write '.' in case of float number
            } else {
                if ((isDigit(infix[i + 1]))||(infix[i + 1] == '.')) {
                    result += infix[i];
                } else {
                   result += infix[i];
                   result += " ";
                }
            }
        } else if (infix[i] == '.') {
            result += infix[i];
            //throw exception if the char is invalid
        } else {
            throw invalid_argument("invalid expression");
        }
    }
    //remove unnecessary space from the end of the expression
    if (result[result.size() - 1] == ' ') {
        result.erase(result.begin() + (result.size() - 1));
    }
    //set the new infix to the result
    infix = result;
}

/*
Is charge of rewriting negative numbers and order of precedence between expressions,
so that the following functions can distinguish them and interpret the expression correctly
*/
void FormExpressionCommand::rewriteNegativeExp() {
    //split the tokens to a vector
    vector<string> tokens = Utils::Split(infix, " ");
    //if the first token is "-"
    if (tokens[0] == "-") {
        //if is -(...) then rewrite it as 0-(...)
        if (tokens[1] == "(") {
            tokens.insert(tokens.begin(), "0");
            //if is -x then rewrite it as (0-x)
        } else if (isNumber(tokens[1])) {
            tokens.insert(tokens.begin() + 2, ")");
            tokens.insert(tokens.begin(), "0");
            tokens.insert(tokens.begin(), "(");
        }
    }
    //do the same for the rest of the tokens
    for (int i = 1; i < tokens.size() - 1; i++) {
        if ((tokens[i] == "-")&&(!isNumber(tokens[i - 1]))) {
            if (tokens[i + 1] == "(") {
                tokens.insert(tokens.begin() + i, "0");
            } else if (isNumber(tokens[i + 1])) {
                tokens.insert(tokens.begin() + i + 2, ")");
                tokens.insert(tokens.begin() + i, "0");
                tokens.insert(tokens.begin() + i, "(");
            }
        }
    }
    //if the expressions contains at least 2 operators in between
    if (tokens.size() >= 5) {
        //for each token
        for (int i = 0; i < tokens.size() - 4; i++) {
            //if there are 2 operators in a row, without parenthesis in between
            if ((isNumber(tokens[i]))&&(isOperator(tokens[i + 1]))&&
            (isNumber(tokens[i + 2]))&&(isOperator(tokens[i + 3]))&&(isNumber(tokens[i + 4]))) {

                /*
                in case the priority of operators was violated, put parenthesis on the 2 operands
                of the leftmost operator
                */
                if (((tokens[i + 1] == "-")&&(tokens[i + 3] == "+"))||
                ((tokens[i + 1] == "-")&&(tokens[i + 3] == "-"))||
                ((tokens[i + 1] == "/")&&(tokens[i + 3] == "/"))||
                ((tokens[i + 1] == "/")&&(tokens[i + 3] == "*"))) {
                    tokens.insert(tokens.begin() + i + 3, ")");
                    tokens.insert(tokens.begin() + i, "(");
                }
            }
        }
    }
    //construct the result to a string
    string result = "";
    for (int i = 0; i < tokens.size(); i++) {
        result += tokens[i];
        result += " ";
    }
    //remove unnecessary space from the end
    result.erase(result.begin() + (result.size() - 1));
    infix = result;
}

/*
in charge of converting the expression from infix form to postfix form,
using Dijakstra Shunting-Yard algorithm
*/
string FormExpressionCommand::convertToPostfix() {
    list<string> queue = {};
    list<string> stack = {};
    //split the infix into vector of tokens
    vector<string> tokens = Utils::Split(infix, " ");
    //for each token
    for (auto& token : tokens) {
        //if is number, put in the queue
        if (isNumber(token)) {
            queue.push_back(token);
            //if is operator
        } else if (isOperator(token)) {
            //while there is an operator with greater precedence on the top of the stack, pop it onto the queue
            while (!stack.empty()) {
                if (isOperator(stack.back())) {
                    if (precedence(stack.back()) > precedence(token)) {
                        queue.push_back(stack.back());
                        stack.pop_back();
                        continue;
                    }
                }
                break;
            }
            //push to the stack
            stack.push_back(token);
            //if is left parenthesis, push onto the stack
        } else if (token == "(") {
            stack.push_back(token);
            // if is right parenthesis
        } else if (token == ")") {
            //while there is not "(" on the top of the stack, pop operator from the stack onto the queue
            while (!stack.empty()) {
                if (stack.back() != "(") {
                    queue.push_back(stack.back());
                    stack.pop_back();
                    continue;
                }
                break;
            }
            //pop "("
            stack.pop_back();
        }
    }
    //while there is an operator at the top of the stack
    while (!stack.empty()) {
        if (isOperator(stack.back())) {
            queue.push_back(stack.back());
        }
        //pop operator from stack onto the queue
        stack.pop_back();
    }
    //construct the postfix string, with space in between
    string result = "";
    for (auto& element : queue) {
        result += element;
        result += " ";
    }
    //erase unnecessary spaces from the end
    result.erase(result.begin() + (result.size() - 1));
    return result;
}

/*
in charge of constructing an expression tree from the postfix form
*/
Expression* FormExpressionCommand::fromPostfixToExpr(string postfix) {
    string s = postfix;
    //split the postfix into tokens
    vector<string> tokens = Utils::Split(s, " ");
    list<string> stack = {};
    double result;

    /*
    for each token from left to right, if it is a number then put it in the queue.
    otherwise if it is an operator, then pop the last two numbers out of the stack,
    run the operator on them, and put the result in the stack
    */
    for (auto &token : tokens) {
        if (token == "+") {
            Expression* right = new Number(stod(stack.back()));
            stack.pop_back();
            Expression* left = new Number(stod(stack.back()));
            stack.pop_back();
            result = (new Plus(left, right))->calculate();
            stack.push_back(to_string(result));
        } else if (token == "-") {
            Expression* right = new Number(stod(stack.back()));
            stack.pop_back();
            Expression* left = new Number(stod(stack.back()));
            stack.pop_back();
            result = (new Minus(left, right))->calculate();
            stack.push_back(to_string(result));
        } else if (token == "*") {
            Expression* right = new Number(stod(stack.back()));
            stack.pop_back();
            Expression* left = new Number(stod(stack.back()));
            stack.pop_back();
            result = (new Mult(left, right))->calculate();
            stack.push_back(to_string(result));
        } else if (token == "/") {
            Expression* right = new Number(stod(stack.back()));
            stack.pop_back();
            Expression* left = new Number(stod(stack.back()));
            stack.pop_back();
            result = (new Div(left, right))->calculate();
            stack.push_back(to_string(result));
        } else {
            stack.push_back(token);
        }
    }
    //return the result expression
    Number* n = new Number(result);
    return n;
}

/*
returns the result expression in a string
*/
string FormExpressionCommand::getResultStr() {
    return result;
}

