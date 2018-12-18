#include "interface.h"

class Plus : public BinaryExpression {

    private:
    Expression* left;
    Expression* right;

    public:
        Plus(Expression* left, Expression* right);
        double Calculate();
};

class Minus : public BinaryExpression {

    private:
    Expression* left;
    Expression* right;

    public:
        Minus(Expression* left, Expression* right);
        double Calculate();
};

class Mult : public BinaryExpression {

    private:
    Expression* left;
    Expression* right;

    public:
        Mult(Expression* left, Expression* right);
        double Calculate();
};

class Div : public BinaryExpression {

    private:
    Expression* left;
    Expression* right;

    public:
        Div(Expression* left, Expression* right);
        double Calculate();
};
