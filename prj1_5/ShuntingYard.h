

#ifndef __MathParser__MathParser__
#define __MathParser__MathParser__

#include "StringTool.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "interface.h"
#include "Utils.h"
#include "Number.h"
#include "BinaryExpressions.h"




class ShuntingYard
{
public:
    //constructors
    ShuntingYard();
    ShuntingYard(string infixExpression);

    //destructor
    ~ShuntingYard();

    void setExpression(string infixExpression);
    void formatExpression();

    string convertToPostfix();

    Expression* fromPostFixToExpr(string postFix);

private:
    //private vector to store the infix tokens
    vector<string> tokens;

    //the operator stack, defined as an object from my Stack.h
    Stack operatorStack;

    //the output queue
    Queue outputQueue;

    //the expression being utilized in the class
    string expression;
};

#endif /* defined(__MathParser__MathParser__) */
