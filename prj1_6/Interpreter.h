#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "interface.h"

class Interpreter {

    private:
        vector<string> lines;
        int currentLine;
        map<string, Command*> commands;
        map<string, double> *symbolTable;
        map<string, string> *pathTable;

    public:
        Interpreter(vector<string> lines, map<string, double> &symbolTable, map<string, string> &pathTable);
        vector<string> Lexer(int currentLine);
        void Parser(vector<string> words);
        int getCurrentLine();
        void setCurrentLine(int line);
};

#endif // INTERPRETER_H
