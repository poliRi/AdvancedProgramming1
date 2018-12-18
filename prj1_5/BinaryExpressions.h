#include "interface.h"

class Plus : public BinaryExpression {


public:
    Plus(Expression *left, Expression *right);

    double Calculate();
};

class Minus : public BinaryExpression {

public:
    Minus(Expression *left, Expression *right);

    double Calculate();
};

class Mult : public BinaryExpression {


public:
    Mult(Expression *left, Expression *right);

    double Calculate();
};

class Div : public BinaryExpression {


public:
    Div(Expression *left, Expression *right);

    double Calculate();
};