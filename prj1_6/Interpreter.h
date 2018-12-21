#include "interface.h"

class Interpreter {

private:
    map<string, Command*> commands;
    map<string, double> symbolTable;

public:
    Interpreter();
    map<string, double> getSymbolTable();
    vector<string> Lexer(string line);
    void Parser(vector<string> words);
};
