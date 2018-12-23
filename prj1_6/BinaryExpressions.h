#ifndef BINARYEXPRESSIONS_H
#define BINARYEXPRESSIONS_H
#include "interface.h"

class Plus : public BinaryExpression {

    public:
        Plus(Expression *left, Expression *right);
        double calculate();
};

class Minus : public BinaryExpression {

    public:
        Minus(Expression *left, Expression *right);
        double calculate();
};

class Mult : public BinaryExpression {

    public:
        Mult(Expression *left, Expression *right);
        double calculate();
};

class Div : public BinaryExpression {

    public:
        Div(Expression *left, Expression *right);
        double calculate();
};

class BoolenExpr : public BinaryExpression {

    public:
        BoolenExpr(Expression *left, Expression *right);
        double calculate();
};

#endif // BINARYEXPRESSIONS_H
