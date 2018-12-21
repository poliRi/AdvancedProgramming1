#include "Interpreter.h"
#include "Utils.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

Interpreter::Interpreter() {}

vector<string> Interpreter::Lexer(string line) {
    vector<string> words = Utils::Split(line, " ");
    if ((words[0] == "openDataServer")&&(commands.count(words[0])<=0)) {
        OpenServerCommand* cmd = new OpenServerCommand();
        commands.insert(pair<string,Command*>(words[0],cmd));
    } else if ((words[0] == "connect")&&(commands.count(words[0])<=0)) {
        ConnectCommand* cmd = new ConnectCommand();
        commands.insert(pair<string,Command*>(words[0],cmd));
    } else if ((words[0] == "print")&&(commands.count(words[0])<=0)) {
        PrintCommand* cmd = new PrintCommand(symbolTable);
        commands.insert(pair<string,Command*>(words[0],cmd));
    } else if ((words[0] == "var")&&(commands.count(words[0])<=0)) {
        DefineVarCommand* cmd = new DefineVarCommand(symbolTable);
        commands.insert(pair<string,Command*>(words[0],cmd));
    } else if ((words[0] == "sleep")&&(commands.count(words[0])<=0)) {
        SleepCommand* cmd = new SleepCommand();
        commands.insert(pair<string,Command*>(words[0],cmd));
    } /*else if (words[0] == "while") {
    }*/






    /*print vector
    for (const auto& res : words) {
           cout << res << endl;
    }*/
    return words;
}

void Interpreter::Parser(vector<string> words) {

}

map<string, double> Interpreter::getSymbolTable(){
    return symbolTable;
}
