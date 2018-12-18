
#include "Stack.h"

Stack::Stack()
{
    stackIndex = 0;

    stackArray = (char**)malloc(sizeof(char*) * stackIndex);

}

Stack::~Stack()
{

}

void Stack::push(Token token)
{
    char* chrToken = new char[token.value().size() + 1];
    strcpy(chrToken, token.value().c_str());

    stackArray[stackIndex] = (char*)chrToken;

    stackIndex++;
    stackArray = (char **)realloc(stackArray, sizeof(char *) * (stackIndex + 1));

}

void Stack::pop(Queue& queue)
{
    queue.push(Token(stackArray[stackIndex - 1]));

    stackArray = (char **)realloc(stackArray, sizeof(char *) * stackIndex - 1);

    --stackIndex;
}

void Stack::freeStack()
{
    free(stackArray);
}

string Stack::pop()
{
    string tempData = stackArray[stackIndex - 1];

    stackArray = (char **)realloc(stackArray, sizeof(char *) * stackIndex - 1);

    --stackIndex;

    return tempData;
}

string Stack::popStr()
{
    return stackArray[stackIndex - 1];
}

bool Stack::isEmpty()
{
    return stackIndex == 0? true: false;
}