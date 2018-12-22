#include "IfCommand.h"

IfCommand::IfCommand(map<string, double> symbolTable) {
    this->symbolTable = symbolTable;
}

void IfCommand::setCondition(ConditionParser* condition) {
    this->condition = condition;
}

void IfCommand::doCommand(vector<string> args) {
    Interpreter* interpreter = new Interpreter(args);
    interpreter->setSymbolTable(symbolTable);
    int currentLine;
    if (condition->isTrue()) {
        for (currentLine = 0; currentLine < args.size() - 1; currentLine++) {
            vector<string> words = interpreter->Lexer(currentLine);
            interpreter->Parser(words);
        }
    }
}



