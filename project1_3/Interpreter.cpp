#include "Interpreter.h"
#include "Utils.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"

Interpreter::Interpreter() {

}

vector<string> Interpreter::Lexer(string line) {
    //vector of all words in line
    vector<string> words = Utils::Split(line, " ");
    if (words[0] == "openDataServer") {
        OpenServerCommand* cmd = new OpenServerCommand();
        commands.insert(pair<string,Command*>(words[0],cmd));
    } else if (words[0] == "connect") {
        ConnectCommand* cmd = new ConnectCommand();
        commands.insert(pair<string,Command*>(words[0],cmd));
    } else if (words[0] == "print") {
        PrintCommand* cmd = new PrintCommand();
        commands.insert(pair<string,Command*>(words[0],cmd));
    } else if (words[0] == "var") {
        DefineVarCommand* cmd = new DefineVarCommand();
        commands.insert(pair<string,Command*>(words[0],cmd));
    } /*else if (words[0] == "while") {

    }*/



    /*print vector
    for (const auto &res : tokens) {

           cout << res << endl;
    }*/


    return words;
}

void Interpreter::Parser(vector<string> words) {
    map<string, Command*>::iterator iter = commands.find(words[0]);
    if (iter != commands.end()) {
        vector<string> params;
        params = words;
        params.erase(params.begin());
        iter->second->doCommand(params);
    }


    //second parameter vector<string>
    //cmd->doCommand(token[0], "rest of tokens here...");
}
