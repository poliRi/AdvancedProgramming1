#include "Interpreter.h"
#include "Utils.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"

Interpreter::Interpreter() {

}

vector<string> Interpreter::Lexer(string line) {
    //vector of all words in line
    vector<string> words;

    //split each line to a new vector, delimited by " ",
    // and add each result vector to the vector<vector<string>> vector
    for (const auto &word : line) {
        words = Utils::Split(line, " ");
    }

    /*print vector
    for (const auto &res : tokens) {

           cout << res << endl;
    }*/
    return words;
}

void Interpreter::Parser(vector<string> words) {
    if (words[0] == "openDataServer") {
        OpenServerCommand* cmd = new OpenServerCommand();
        vector<string> params;
        params = words;
        params.erase(params.begin());
        cmd->doCommand(params);

    }
    if (words[0] == "connect") {
        ConnectCommand* cmd = new ConnectCommand();
        vector<string> params;
        params = words;
        params.erase(params.begin());
        cmd->doCommand(params);
    }

    /*if (words[0] == "var") {
    }
    if (words[0] == "while")
    if (words[0] == "print")*/

    //second parameter vector<string>
    //cmd->doCommand(token[0], "rest of tokens here...");
}
