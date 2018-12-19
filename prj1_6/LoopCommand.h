//
// Created by Polina Rabinovich on 18/12/2018.
//

#ifndef PROJECT1_LOOPCOMMAND_H
#define PROJECT1_LOOPCOMMAND_H

#include "ConditionParser.h"

class LoopCommand : public ConditionParser {

private:
    vector<Command*> commands;
public:
    void doCommand(vector<string> args);

};


#endif //PROJECT1_LOOPCOMMAND_H
