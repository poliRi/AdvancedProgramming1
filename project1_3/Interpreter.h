#include "interface.h"

class Interpreter {

    private:
        map<string, Command*> commands;

    public:
        Interpreter();
        vector<string> Lexer(string line);
        void Parser(vector<string> words);
};
