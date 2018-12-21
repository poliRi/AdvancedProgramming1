//
// Created by Polina Rabinovich on 18/12/2018.
//

#ifndef PROJECT1_LOOPCOMMAND_H
#define PROJECT1_LOOPCOMMAND_H

#include "interface.h"



class LoopCommand : public Command {

private:

    vector<Command*> allCommands;
    Expression* cond;
    map<string, double>* symbolTable;

public:
    LoopCommand(Expression* condition, vector<Command*>);

    void doCommand(vector<string> commands);

    void RunAllNestedCommands(vector<Command*> commands, vector<string> allLoop);


};


#endif //PROJECT1_LOOPCOMMAND_H
