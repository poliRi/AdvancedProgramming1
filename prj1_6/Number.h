#include "interface.h"

class Number : public Expression {

private:
    double value;

public:
    Number(double value);
    double calculate();
};
