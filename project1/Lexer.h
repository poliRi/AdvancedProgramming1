//
// Created by Polina Rabinovich on 10/12/2018.
//

#ifndef PROJECT1_LEXER_H
#define PROJECT1_LEXER_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "ILexer.h"
#include "Utils.h"

#define DELIMITER " "
#define ENDOFLINE "\n"

using namespace std;

class Lexer : public ILexer {
private:

public:
    vector<vector<string> > Lex(string path) {
        ifstream file;
        file.open(path);
        vector<vector<string> > result;
        //split string to lines in file by "\n"
        auto lines = Utils::split(file, "\n");
        file.close();

        //split each line to a new vector, delimited by " ",
        // and add each result vector to the vector<vector<string>> vector
        for (const auto &line : lines) {
            auto tokens = Utils::split(line, " ");
            result.push_back(tokens);
        }
//print vector
//        for (const auto &res : result) {
//            for (auto vec :res)
//                cout << vec << endl;
//        }

        return result;
    }


};


#endif //PROJECT1_LEXER_H
