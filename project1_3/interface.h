#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
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

using namespace std;

class Command {

    public:
        virtual void doCommand(vector<string> args) = 0;
};

class Expression {

    public:
        virtual double Calculate() = 0;
};

class BinaryExpression : public Expression {
};

#endif

