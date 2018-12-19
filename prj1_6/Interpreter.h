#include "interface.h"

class Interpreter {

    private:
        map<string, Command*> commands;
        map<string, double> symTbl;

    public:
        map<string, double> getSymbolTable();
        Interpreter();
        vector<string> Lexer(string line);
        void Parser(vector<string> words);
};
