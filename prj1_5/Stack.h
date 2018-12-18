

#ifndef __MathParser__Stack__
#define __MathParser__Stack__

#include "Token.h"
#include "Queue.h"
#include <iostream>
#include <string>

using namespace std;

class Stack
{
public:
    Stack();
    ~Stack();

    void push(Token token);
    void pop(Queue& queue);
    void freeStack();

    string pop();
    string popStr();

    bool isEmpty();

private:
    char** stackArray;

    int stackIndex;
};

#endif /* defined(__MathParser__Stack__) */
