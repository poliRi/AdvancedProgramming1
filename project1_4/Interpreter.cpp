#include "Interpreter.h"
#include "Utils.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"

Interpreter::Interpreter() {

}

vector<string> Interpreter::Lexer(string path) {
    vector<string> words;
    ifstream file;
    file.open(path);
    //split string to lines in file by "\n"
    auto lines = Utils::Split(file, "\n");
    file.close();
    for (auto line : lines) {
        vector<string> lineWords = Utils::Split(line, " ");
         if (lineWords[0] == "openDataServer") {
                OpenServerCommand* cmd = new OpenServerCommand();
                commands.insert(pair<string,Command*>(lineWords[0],cmd));
            } else if (lineWords[0] == "connect") {
                ConnectCommand* cmd = new ConnectCommand();
                commands.insert(pair<string,Command*>(lineWords[0],cmd));
            } else if (lineWords[0] == "print") {
                PrintCommand* cmd = new PrintCommand();
                commands.insert(pair<string,Command*>(lineWords[0],cmd));
            } else if (lineWords[0] == "var") {
                DefineVarCommand* cmd = new DefineVarCommand();
                commands.insert(pair<string,Command*>(lineWords[0],cmd));
            } /*else if (lineWords[0] == "while") {

            }*/
        for (auto word : lineWords) {
            words.push_back(word);
        }
    }

    /*print vector
    for (const auto &res : tokens) {

           cout << res << endl;
    }*/

    return words;
}

void Interpreter::Parser(vector<string> words) {
    int index = 0;
    while (index < words.size()) {
        map<string, Command*>::iterator iter = commands.find(words[index]);
        if (iter != commands.end()) {
            vector<string> args;
            for (int i = 0; i < iter->second->getNumOfArgs(); i++) {
                args.push_back(words[index + 1 + i]);
            }
            index += iter->second->doCommand(args);
        }
    }


    //second parameter vector<string>
    //cmd->doCommand(token[0], "rest of tokens here...");
}
