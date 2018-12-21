#include "BinaryExpressions.h"

Plus::Plus(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Plus::calculate() {
   return left->calculate() + right->calculate();
}

Minus::Minus(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Minus::calculate() {
   return left->calculate() - right->calculate();
}

Mult::Mult(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Mult::calculate() {
   return left->calculate() * right->calculate();
}

Div::Div(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Div::calculate() {
   return left->calculate() / right->calculate();
}
