#include "WhileCommand.h"

WhileCommand::WhileCommand(map<string, double> symbolTable) {
    this->symbolTable = symbolTable;
}

void WhileCommand::setCondition(ConditionParser* condition) {
    this->condition = condition;
}

void WhileCommand::doCommand(vector<string> args) {
    Interpreter* interpreter = new Interpreter(args);
    interpreter->setSymbolTable(symbolTable);
    int currentLine;
    while (condition->isTrue()) {
        for (currentLine = 0; currentLine < args.size() - 1; currentLine++) {
            vector<string> words = interpreter->Lexer(currentLine);
            interpreter->Parser(words);
        }
    }
}


