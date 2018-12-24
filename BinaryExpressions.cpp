#include "BinaryExpressions.h"

/*
plus binary expression: constructor
*/
Plus::Plus(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

/*
plus binary expression: calculates expression
*/
double Plus::calculate() {
   return left->calculate() + right->calculate();
}

/*
minus binary expression: constructor
*/
Minus::Minus(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

/*
minus binary expression: calculates expression
*/
double Minus::calculate() {
   return left->calculate() - right->calculate();
}

/*
multipication binary expression: constructor
*/
Mult::Mult(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

/*
multipication binary expression: calculates expression
*/
double Mult::calculate() {
   return left->calculate() * right->calculate();
}

/*
division binary expression: constructor
*/
Div::Div(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

/*
division binary expression: calculates expression
*/
double Div::calculate() {
   return left->calculate() / right->calculate();
}
