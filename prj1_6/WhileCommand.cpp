#include "WhileCommand.h"

WhileCommand::WhileCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

void WhileCommand::setCondition(ConditionParser* condition) {
    this->condition = condition;
}

void WhileCommand::doCommand(vector<string> args) {
    Interpreter* interpreter = new Interpreter(args, *symbolTable, *pathTable);
    while (condition->isTrue()) {
        while (interpreter->getCurrentLine() < args.size()) {
            vector<string> words = interpreter->Lexer(interpreter->getCurrentLine());
            interpreter->Parser(words);
        }
        interpreter->setCurrentLine(0);
    }
}


