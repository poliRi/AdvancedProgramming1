//
// Created by Polina Rabinovich on 18/12/2018.
//

#include "IfCommand.h"

IfCommand::IfCommand(Expression *condition, vector<Command *> commands) {
    cond = condition;
    allCommands = commands;
}


void IfCommand::doCommand(vector<string> allLoop) {
    if (cond->calculate()) {
        RunAllNestedCommands(allCommands, allLoop);
    }
}

void IfCommand::RunAllNestedCommands(vector<Command *> commands, vector<string> allLoop) {
    for (auto &command : commands) {
        command->doCommand(allLoop);
    }
}