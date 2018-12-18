

#include "ShuntingYard.h"

//constructor
ShuntingYard::ShuntingYard() {

}

//alternative contructor to set the infix expression
ShuntingYard::ShuntingYard(string infixExpression) {
    expression = infixExpression;
}

//destructor
ShuntingYard::~ShuntingYard() {

}

//function to set the infix expression
void ShuntingYard::setExpression(string infixExprression) {
    expression = infixExprression;
}

/* formats the infix expression such that there will be one space between each token, which will allow the tokenizing process to be optimized. For example, if the user were to enter 1+4  *( 5), the function would format it to 1 + 4 * ( 5 ), and then convert it into an array of tokens */

void ShuntingYard::formatExpression() {
    //initialls trims the expression
    expression = trim(expression);

    //loops through each character in the expression
    for (int i = 0; i < expression.size(); i++) {
        //initializes a string for the current character and allocates it one block of memory
        string strExpr = (char *) malloc(sizeof(char) * 1);
        strExpr = expression[i];

        //if the current character is an operator of parenthesis, add a space before and after it
        if ((Token(strExpr).isOperator() || Token(strExpr).isLeftParenthesis()) ||
            Token(strExpr).isRightParenthesis()) {
            expression.insert(i, " ");
            expression.insert(i + 2, " ");

            //increment i by two to prevent an infinite loop
            i += 2;
        }
    }

    //splits the expression into tokens which will be stored in the tokens vector
    split(tokens, expression.c_str(), " ");
}

//main function that implements the shunting yard algorithm
string ShuntingYard::convertToPostfix() {
    //initialization of the return string
    string postfixExpression;

    //iterates through the token vector
    for (int i = 0; i < tokens.size(); i++) {
        //initializes a Token for the current element in the vector
        Token currentToken(tokens.at(i));

        //checks if the token is an operator
        if (currentToken.isOperator()) {
            //checks if the operator stack is empty
            if (!operatorStack.isEmpty()) {
                //initializes a seperate token for the top of the stack
                Token topToken(operatorStack.popStr());

                //gets the associativity and precedence of the current token
                int currentAssoc = currentToken.associativity();
                int currentPrecedence = currentToken.precedence();

                //compares the token properties of the current token to the top of the stack and performs additional boolean operations through a while loop
                while (!operatorStack.isEmpty() && ((currentAssoc == 0 && currentPrecedence <= topToken.precedence()) ||
                                                    (currentAssoc == 1 && currentPrecedence < topToken.precedence()))) {
                    //pops the top element of the stack onto the output queue
                    operatorStack.pop(outputQueue);
                }
            }

            //pushes the operator onto the stack
            operatorStack.push(currentToken);
        } else if (currentToken.isLeftParenthesis()) {
            //pushes the parenthesis onto the stack
            operatorStack.push(currentToken);
        } else if (currentToken.isRightParenthesis()) {
            //pops every element on the stack until the matching parenthesis is found, but is disregarded
            while (!Token(operatorStack.popStr()).isLeftParenthesis()) {
                operatorStack.pop(outputQueue);
            }

            operatorStack.pop();
        } else {
            //pushes the token directly to the queue
            outputQueue.push(currentToken);
        }
    }

    //clears the stack in a LIFO format
    while (!operatorStack.isEmpty()) {
        operatorStack.pop(outputQueue);
    }

    //appends the elements of the output queue to the final string
    while (outputQueue.size() > 0) {
        postfixExpression += (string) outputQueue.pop() + " ";
    }

    //clears memory used in the dynamic array
    operatorStack.freeStack();

    //sets the expression to the postfix expression in case an implementation of the postfix evaluater is to be used
    expression = postfixExpression;
    cout << postfixExpression << endl;
    //returns the postfix expression
    return postfixExpression;
}


Expression *fromPostFixToExpr(string postfix) {

    string spl = postfix;

    vector<string> tokens = Utils::Split(spl, " ");
    double result;
    Stack* stack = new Stack();
    for(auto &token : tokens){
        if (token == "+"){
            Expression* right = new Number(stoi(stack->pop()));
            Expression* left = new Number(stoi(stack->pop()));
            result = (new Plus(left, right))->Calculate();
            Token t(to_string(result));
            stack->push(t);
        }
        else if (token == "-"){
        Expression* right = new Number(stoi(stack->pop()));
        Expression* left = new Number(stoi(stack->pop()));
        result = (new Minus(left, right))->Calculate();
        Token t(to_string(result));
        stack->push(t);
        }
        else if (token == "*"){
            Expression* right = new Number(stoi(stack->pop()));
            Expression* left = new Number(stoi(stack->pop()));
            result = (new Mult(left, right))->Calculate();
            Token t(to_string(result));
            stack->push(t);
        }
        else if (token == "/"){
            Expression* right = new Number(stoi(stack->pop()));
            Expression* left = new Number(stoi(stack->pop()));
            result = (new Div(left, right))->Calculate();
            Token t(to_string(result));
            stack->push(t);
        }else {
            Token t(token);
            stack->push(t);
        }
    }
    Number* res = new Number(result);

    return res;

}
