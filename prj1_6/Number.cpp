#include "Number.h"

/*
number expression: constructor
*/
Number::Number(double value) {
    this->value = value;
}

/*
calculates the value of the number
*/
double Number::calculate() {
   return value;
}
