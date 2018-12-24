#ifndef BINARYEXPRESSIONS_H
#define BINARYEXPRESSIONS_H
#include "interface.h"

/*
plus binary expression
*/
class Plus : public BinaryExpression {

    public:
        Plus(Expression *left, Expression *right);
        double calculate();
};

/*
minus binary expression
*/
class Minus : public BinaryExpression {

    public:
        Minus(Expression *left, Expression *right);
        double calculate();
};

/*
multipication binary expression
*/
class Mult : public BinaryExpression {

    public:
        Mult(Expression *left, Expression *right);
        double calculate();
};

/*
division binary expression
*/
class Div : public BinaryExpression {

    public:
        Div(Expression *left, Expression *right);
        double calculate();
};

#endif // BINARYEXPRESSIONS_H
