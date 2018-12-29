#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "interface.h"

/*
class Interpreter is in charge of interpreting and executing code lines.
it does this by splitting the line into tokens, parsing, and calling the right commands to be executed
*/
class Interpreter {

    private:
        vector<string> lines;
        int currentLine;
        map<string, Command*> commands;
        map<string, double> *symbolTable;
        map<string, string> *pathTable;
        map<string, bool> *isAssigned;

    public:
        Interpreter(vector<string> lines, map<string, double> &symbolTable, map<string, string> &pathTable, map<string, bool> &isAssigned);
        vector<string> Lexer(int currentLine);
        void Parser(vector<string> words);
        int getCurrentLine();
        void setCurrentLine(int line);
        void setSingleLineToRead(string line);
        ~Interpreter();
};

#endif // INTERPRETER_H
