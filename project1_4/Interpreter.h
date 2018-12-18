#include "interface.h"

class Interpreter {

    private:
        map<string, Command*> commands;
        map<string, double> symbolTable;

    public:
        Interpreter();
        vector<string> Lexer(string path);
        void Parser(vector<string> words);
};
