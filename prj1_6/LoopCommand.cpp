//
// Created by Polina Rabinovich on 18/12/2018.
//

#include "LoopCommand.h"
#include "Interpreter.h"


LoopCommand::LoopCommand(Expression *condition, vector<Command *> commands) {
    cond = condition;
    allCommands = commands;
}


void LoopCommand::doCommand(vector<string> allLoop) {
    Interpreter *inter;

    while (cond->calculate()) {
        for (auto line : allLoop) {
            vector<string> words = inter->Lexer(line);
            inter->Parser(words);
        }
    }
}
