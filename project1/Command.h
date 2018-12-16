//
// Created by Polina Rabinovich on 10/12/2018.
//

#ifndef PROJECT1_COMMAND_H
#define PROJECT1_COMMAND_H
#include <string>
using namespace std;
class Command {

public:
    virtual int execute (vector<string> args) = 0;

};


#endif //PROJECT1_COMMAND_H
