#include "FormExpressionCommand.h"
#include "Utils.h"
#include "Number.h"
#include "BinaryExpressions.h"

FormExpressionCommand::FormExpressionCommand(map<string, double> &symbolTable) {
    this->symbolTable = &symbolTable;
}

void FormExpressionCommand::doCommand(vector<string> args) {
    if ((args[0].size() == 0)||(args[0] == " ")) {
        throw logic_error("invalid expression");
    }
    this->infix = args[0];
    evaluateVars();
    if (isSignelNumber()) {
        e = new Number(stod(infix));
        //cout << e->calculate() << endl;
        result = to_string(e->calculate());
    } else {
        toTokens();
        rewriteNegativeExp();
        //cout << infix << endl;
        string postfix = convertToPostfix();
        //cout << postfix << endl;
        e = fromPostfixToExpr(postfix);
        //cout << e->calculate() << endl;
        result = to_string(e->calculate());
    }
}

void FormExpressionCommand::evaluateVars() {
    map<string,double>::iterator iter;
    for (iter = symbolTable->begin(); iter != symbolTable->end(); ++iter) {
        string var = iter->first;
        string value = to_string(iter->second);
        while (infix.find(var) != string::npos) {
            int pos = infix.find(var);
            infix.replace(pos, var.size(), value);
        }
    }
}

bool FormExpressionCommand::isSignelNumber() {
    for (int i = 0; i < infix.size(); i++) {
        if ((infix[i] == '+')||(infix[i] == '-')||(infix[i] == '*')||(infix[i] == '/')||
        (infix[i] == '(')||(infix[i] == ')')) {
            return false;
        }
    }
    return true;
}

int FormExpressionCommand::precedence(string oper) {
    if ((oper == "+")||(oper == "-")) {
        return 1;
    } else if ((oper == "*")||(oper == "/")) {
        return 2;
    }
}

bool FormExpressionCommand::isDigit(char c) {
    return ((c == '0')||(c == '1')||(c == '2')||(c == '3')||(c == '4')||(c == '5')||(c == '6')||
    (c == '7')||(c == '8')||(c == '9'));
}

bool FormExpressionCommand::isNumber(string token) {
    if (token[0] == '-') {
        return (token.size() >= 2);
    }
    return isDigit(token[0]);
}

bool FormExpressionCommand::isOperator(string token) {
    return ((token == "+")||(token == "-")||(token == "*")||(token == "/"));
}

void FormExpressionCommand::toTokens() {
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
    for (int i = 0; i < infix.size(); i++) {
        if ((infix[i] == '+')||(infix[i] == '-')||(infix[i] == '*')||(infix[i] == '/')||
        (infix[i] == '(')||(infix[i] == ')')) {
            result += infix[i];
            result += " ";
        } else if (infix[i] == ' ') {
            continue;
        } else if (isDigit(infix[i])) {
            if (i + 1 >= infix.size()) {
                result += infix[i];
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
        } else {
            throw invalid_argument("invalid expression");
        }
    }
    if (result[result.size() - 1] == ' ') {
        result.erase(result.begin() + (result.size() - 1));
    }
    infix = result;
}

void FormExpressionCommand::rewriteNegativeExp() {
    vector<string> tokens = Utils::Split(infix, " ");
    if (tokens[0] == "-") {
        if (tokens[1] == "(") {
            tokens.insert(tokens.begin(), "0");
        } else if (isNumber(tokens[1])) {
            tokens.insert(tokens.begin() + 2, ")");
            tokens.insert(tokens.begin(), "0");
            tokens.insert(tokens.begin(), "(");
        }
    }
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
    if (tokens.size() >= 5) {
        for (int i = 0; i < tokens.size() - 4; i++) {
            if ((isNumber(tokens[i]))&&(isOperator(tokens[i + 1]))&&
            (isNumber(tokens[i + 2]))&&(isOperator(tokens[i + 3]))&&(isNumber(tokens[i + 4]))) {
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
    string result = "";
    for (int i = 0; i < tokens.size(); i++) {
        result += tokens[i];
        result += " ";
    }
    result.erase(result.begin() + (result.size() - 1));
    infix = result;
}

string FormExpressionCommand::convertToPostfix() {
    list<string> queue = {};
    list<string> stack = {};
    vector<string> tokens = Utils::Split(infix, " ");
    for (auto& token : tokens) {
        if (isNumber(token)) {
            queue.push_back(token);
        } else if (isOperator(token)) {
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
            stack.push_back(token);
        } else if (token == "(") {
            stack.push_back(token);
        } else if (token == ")") {
            while (!stack.empty()) {
                if (stack.back() != "(") {
                    queue.push_back(stack.back());
                    stack.pop_back();
                    continue;
                }
                break;
            }
            stack.pop_back();
        }
    }
    while (!stack.empty()) {
        if (isOperator(stack.back())) {
            queue.push_back(stack.back());
        }
        stack.pop_back();
    }
    string result = "";
    for (auto& element : queue) {
        result += element;
        result += " ";
    }
    result.erase(result.begin() + (result.size() - 1));
    return result;
}

Expression* FormExpressionCommand::fromPostfixToExpr(string postfix) {
    string s = postfix;
    vector<string> tokens = Utils::Split(s, " ");
    list<string> stack = {};
    double result;
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
    Number* n = new Number(result);
    return n;
}

string FormExpressionCommand::getResultStr() {
    return result;
}

