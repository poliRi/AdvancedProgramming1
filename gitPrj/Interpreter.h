//
// Created by Polina Rabinovich on 17/12/2018.
//

#ifndef PROJECT1_INTERPRETER_H
#define PROJECT1_INTERPRETER_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include <map>


class Interpreter {
private:

    map<string, Command*> commands;
    map<string, double> symTbl;

public:

    Interpreter(){

    }

    vector<string> Lexer(string line) {
        //vector of all words in line
        vector<string> words;

        //split each line to a new vector, delimited by " ",
        // and add each result vector to the vector<vector<string>> vector
        for (const auto &word : line) {
            words = Utils::split(line, " ");
        }

        //print vector
//        for (const auto &res : tokens) {
//
//                cout << res << endl;
//        }
            return words;

    }


        void Parser(vector<string> words) {


        if(words[0] == "openDataServer"){
            OpenServerCommand* cmd = new OpenServerCommand();
            vector<string> params;
            params = words;
            params.erase(params.begin());
            cmd->doCommand(params);

        }
        if(words[0] == "connect"){
            ConnectCommand* cmd = new ConnectCommand();
            vector<string> params;
            params = words;
            params.erase(params.begin());
            cmd->doCommand(params);
        }

        if(words[0] == "var"){
        symTbl
        }
        if(words[0] == "while")
        if(words[0] == "print")

            //second parameter vector<string>
//            cmd->doCommand(token[0], "rest of tokens here...");

    }
};


#endif //PROJECT1_INTERPRETER_H
