//
// Created by Polina Rabinovich on 18/12/2018.
//

#ifndef PROJECT1_IFCOMMAND_H
#define PROJECT1_IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser{

public:
    void doCommand(vector<string> args);

};


#endif //PROJECT1_IFCOMMAND_H
