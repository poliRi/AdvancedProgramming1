#include "Interpreter.h"
#include "Utils.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "FormExpressionCommand.h"
#include "AssignmentCommand.h"

Interpreter::Interpreter() {
    this->symbolTable = {};
    this->commands = {};
    commands.insert(pair<string,Command*>("openDataServer",(new OpenServerCommand())));
    commands.insert(pair<string,Command*>("connect",(new ConnectCommand())));
    commands.insert(pair<string,Command*>("print",(new PrintCommand(symbolTable))));
    commands.insert(pair<string,Command*>("var",(new DefineVarCommand(symbolTable))));
    commands.insert(pair<string,Command*>("sleep",(new SleepCommand())));
    commands.insert(pair<string,Command*>("assignment",(new AssignmentCommand(symbolTable))));
    //commands.insert(pair<string,Command*>("bind",(new BindCommand())));
    commands.insert(pair<string,Command*>("formExpression",(new FormExpressionCommand(symbolTable))));

    // insert loop commands


}

vector<string> Interpreter::Lexer(string line) {
    vector<string> words = Utils::Split(line, " ");
    /*print vector
    for (const auto& res : words) {
           cout << res << endl;
    }*/
    return words;
}

void Interpreter::Parser(vector<string> words) {
    vector<string> params = {};
    if ((words[0] == "openDataServer")||(words[0] == "connect")||(words[0] == "print")||(words[0] == "sleep")) {
        Command* c = commands.find(words[0])->second;
        params = words;
        params.erase(params.begin());
        c->doCommand(params);
    } else if (words[0] == "var") {
        Command* c = commands.find(words[0])->second;
        params.push_back(words[1]);
        c->doCommand(params);
        if (words.size() > 2) {
            params.clear();
            if (words[3] == "bind") {
                Command* bnd = commands.find("bind")->second;
                params.push_back(words[1]);
                params.push_back(words[4]);
                bnd->doCommand(params);
            } else {
                string expressionsStr = "";
                for (int i = 3; i < words.size(); i++) {
                    expressionsStr += words[i];
                }
                FormExpressionCommand* evaluate = (FormExpressionCommand*)commands.find("formExpression")->second;
                params.push_back(expressionsStr);
                evaluate->doCommand(params);
                params.clear();
                Command* ass = commands.find("assignment")->second;
                params.push_back(words[1]);
                params.push_back(evaluate->getResultStr());
                ass->doCommand(params);
            }
        }
    } else if (words[0] == "while") {

    } else if (words[0] == "if") {

    } else if (symbolTable.count(words[0]) > 0) {
        if (words[2] == "bind") {
                Command* bnd = commands.find("bind")->second;
                params.push_back(words[0]);
                params.push_back(words[3]);
                bnd->doCommand(params);
            } else {
                string expressionsStr = "";
                for (int i = 2; i < words.size(); i++) {
                    expressionsStr += words[i];
                }
                FormExpressionCommand* evaluate = (FormExpressionCommand*)commands.find("formExpression")->second;
                params.push_back(expressionsStr);
                evaluate->doCommand(params);
                params.clear();
                Command* ass = commands.find("assignment")->second;
                params.push_back(words[0]);
                params.push_back(evaluate->getResultStr());
                ass->doCommand(params);
            }
    } else {
        throw logic_error("unrecognized operation");
    }
}

map<string, double> Interpreter::getSymbolTable() {
    return symbolTable;
}
