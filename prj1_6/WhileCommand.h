//
// Created by Polina Rabinovich on 18/12/2018.
//

#ifndef PROJECT1_WHILECOMMAND_H
#define PROJECT1_WHILECOMMAND_H

#include "interface.h"



class WhileCommand : public Command {

private:

    vector<Command*> allCommands;
    Expression* cond;
    map<string, double>* symbolTable;

public:
    WhileCommand(Expression* condition, vector<Command*>);

    void doCommand(vector<string> commands);

    void RunAllNestedCommands(vector<Command*> commands, vector<string> allLoop);


};


#endif //PROJECT1_WHILECOMMAND_H
