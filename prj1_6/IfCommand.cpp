#include "IfCommand.h"

IfCommand::IfCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

void IfCommand::setCondition(ConditionParser* condition) {
    this->condition = condition;
}

void IfCommand::doCommand(vector<string> args) {
    Interpreter* interpreter = new Interpreter(args, *symbolTable, *pathTable);
    if (condition->isTrue()) {
        while (interpreter->getCurrentLine() < args.size()) {
            vector<string> words = interpreter->Lexer(interpreter->getCurrentLine());
            interpreter->Parser(words);
        }
    }
}



