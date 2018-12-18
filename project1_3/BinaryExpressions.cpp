#include "BinaryExpressions.h"

Plus::Plus(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Plus::Calculate() {
   return left->Calculate() + right->Calculate();
}

Minus::Minus(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Minus::Calculate() {
   return left->Calculate() - right->Calculate();
}

Mult::Mult(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Mult::Calculate() {
   return left->Calculate() * right->Calculate();
}

Div::Div(Expression* left, Expression* right) {
    this->left = left;
    this->right = right;
}

double Div::Calculate() {
   return left->Calculate() / right->Calculate();
}
