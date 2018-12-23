#include "Interpreter.h"
#include "Utils.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "FormExpressionCommand.h"
#include "AssignmentCommand.h"
#include "ConditionParser.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "BindCommand.h"


Interpreter::Interpreter(vector<string> lines, map<string, double> &symbolTable, map<string, string> &pathTable) {
    this->lines = lines;
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
    this->commands = {};
    this->currentLine = 0;
    commands.insert(pair<string,Command*>("openDataServer",(new OpenServerCommand())));
    commands.insert(pair<string,Command*>("connect",(new ConnectCommand())));
    commands.insert(pair<string,Command*>("print",(new PrintCommand(symbolTable))));
    commands.insert(pair<string,Command*>("var",(new DefineVarCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("sleep",(new SleepCommand())));
    commands.insert(pair<string,Command*>("assignment",(new AssignmentCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("bind",(new BindCommand(pathTable))));
    commands.insert(pair<string,Command*>("formExpression",(new FormExpressionCommand(symbolTable))));
    commands.insert(pair<string,Command*>("while",(new WhileCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("if",(new IfCommand(symbolTable, pathTable))));
}

vector<string> Interpreter::Lexer(int line) {
    vector<string> words = Utils::Split(lines[line], " ");
    /*//print vector
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
    } else if ((words[0] == "while")||(words[0] == "if")) {
         vector<string> conditionTokens = {};
         for (int i = 1; ((i < words.size())&&(words[i] != "{")); i++) {
            conditionTokens.push_back(words[i]);
         }
         currentLine++;
         if (words.back() != "{") {
            currentLine++;
         }
         ConditionParser* condition = new ConditionParser(conditionTokens, *symbolTable);
         while (lines[currentLine].front() != '}') {
            if (lines[currentLine].front() == '\t') {
                lines[currentLine].erase(lines[currentLine].begin());
            }
            params.push_back(lines[currentLine]);
            currentLine++;
         }
         if (words[0] == "while") {
             WhileCommand* whileCmd = (WhileCommand*)commands.find("while")->second;
             whileCmd->setCondition(condition);
             whileCmd->doCommand(params);
         } else if (words[0] == "if") {
            IfCommand* ifCmd = (IfCommand*)commands.find("if")->second;
            ifCmd->setCondition(condition);
            ifCmd->doCommand(params);
         }
    } else if (symbolTable->count(words[0]) > 0) {
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
    } else if (words[0].size() == 0) {
    } else {
         throw logic_error("unrecognized operation");
    }
    currentLine++;
}

int Interpreter::getCurrentLine() {
    return this->currentLine;
}

void Interpreter::setCurrentLine(int line) {
    this->currentLine = line;
}
