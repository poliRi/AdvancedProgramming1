//
// Created by Polina Rabinovich on 10/12/2018.
//

#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H

#include <string>
#include <vector>
#include "CommandManager.h"


using namespace std;

class Parser {
private:
    CommandManager *cmd;
public:
    Parser() {
        cmd = new CommandManager();

    }

    void parse(vector<vector<string>> tokens) {
        for (auto token : tokens)

            //second parameter vector<string>
            cmd->execute(token[0], "rest of tokens here...");


    }
};


#endif //PROJECT1_PARSER_H
