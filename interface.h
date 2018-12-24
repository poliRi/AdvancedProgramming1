#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include<map>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include<list>

using namespace std;

/*
Command interface. has the doCommand method
*/
class Command {

public:
    virtual void doCommand(vector<string> args) = 0;
};

/*
Expression interface. has the calculate method
*/
class Expression {

public:
    virtual double calculate() = 0;
};

/*
BinaryExpression abstract class. holds 2 members of type expression: left operand and right operand
*/
class BinaryExpression : public Expression {
protected:
    Expression *left;
    Expression *right;
};

#endif
