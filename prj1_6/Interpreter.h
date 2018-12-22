#include "interface.h"

class Interpreter {

    private:
        vector<string> lines;
        int currentLine;
        map<string, Command*> commands;
        map<string, double> symbolTable;

    public:
        Interpreter(vector<string> lines);
        map<string, double> setSymbolTable(map<string, double> symbolTable);
        vector<string> Lexer(int &currentLine);
        void Parser(vector<string> words);
};
