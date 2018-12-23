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
    int currentLine;
    while (condition->isTrue()) {
        for (currentLine = 0; currentLine < args.size(); currentLine++) {
            vector<string> words = interpreter->Lexer(currentLine);
            interpreter->Parser(words);
        }
    }
}


