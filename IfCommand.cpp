#include "IfCommand.h"

/*
IfCommand: constructor
*/
IfCommand::IfCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    //hold a reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

/*
sets the boolean condition of the command
*/
void IfCommand::setCondition(ConditionParser* condition) {
    this->condition = condition;
}

/*
executes the given lines if the given condition is true
*/
void IfCommand::doCommand(vector<string> args) {
    Interpreter* interpreter = new Interpreter(args, *symbolTable, *pathTable);
    if (condition->isTrue()) {
        //for each line the interpreter is reading, lex and parse
        while (interpreter->getCurrentLine() < args.size()) {
            vector<string> words = interpreter->Lexer(interpreter->getCurrentLine());
            interpreter->Parser(words);
        }
    }
}



