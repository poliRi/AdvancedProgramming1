//
// Created by Polina Rabinovich on 18/12/2018.
//

#include "WhileCommand.h"
#include "Interpreter.h"


WhileCommand::WhileCommand(Expression *condition, vector<Command *> commands) {
    cond = condition;
    allCommands = commands;
}


void WhileCommand::doCommand(vector<string> allLoop) {
//    Interpreter *inter;
//
//    while (cond->calculate()) {
//        for (auto line : allLoop) {
//            vector<string> words = inter->Lexer(line);
//            inter->Parser(words);
//        }
//    }


    while (cond->calculate()) {
        vector<string> copyAllLoop;
        copyAllLoop = allLoop;
        RunAllNestedCommands(allCommands, copyAllLoop);
    }
}

void WhileCommand::RunAllNestedCommands(vector<Command *> commands, vector<string> copyAllLoop) {
    for (auto &command : commands) {
        command->doCommand(copyAllLoop);
    }
}
