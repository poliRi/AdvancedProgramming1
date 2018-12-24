#include "WhileCommand.h"

/*
WhileCommand: constructor
*/
WhileCommand::WhileCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    //hold a reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

/*
sets the boolean condition of the command
*/
void WhileCommand::setCondition(ConditionParser* condition) {
    this->condition = condition;
}

/*
executes the given lines while the given condition is true
*/
void WhileCommand::doCommand(vector<string> args) {
    Interpreter* interpreter = new Interpreter(args, *symbolTable, *pathTable);
    while (condition->isTrue()) {
        //for each line the interpreter is reading, lex and parse
        while (interpreter->getCurrentLine() < args.size()) {
            vector<string> words = interpreter->Lexer(interpreter->getCurrentLine());
            interpreter->Parser(words);
        }
        //initialize the index of the current line in case the execution will be repeated
        interpreter->setCurrentLine(0);
    }
}


