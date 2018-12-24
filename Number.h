#ifndef NUMBER_H
#define NUMBER_H
#include "interface.h"

/*
number exprssion
*/
class Number : public Expression {

    private:
        double value;

    public:
        Number(double value);
        double calculate();
};

#endif // NUMBER_H
