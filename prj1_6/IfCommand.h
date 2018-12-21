//
// Created by Polina Rabinovich on 18/12/2018.
//

#ifndef PROJECT1_IFCOMMAND_H
#define PROJECT1_IFCOMMAND_H

#include "interface.h"

class IfCommand : public Command {

private:

    vector<Command *> allCommands;
    Expression *cond;
    map<string, double> *symbolTable;

public:
    IfCommand(Expression *condition, vector<Command *>);

    void doCommand(vector<string> commands);

    void RunAllNestedCommands(vector<Command *> commands, vector<string> allLoop);

};


#endif //PROJECT1_IFCOMMAND_H
