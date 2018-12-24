#include "PrintCommand.h"

/*
PrintCommand: constructor
*/
PrintCommand::PrintCommand(map<string, double> &symbolTable) {
    //hold reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
}

/*
in charge of printing the given expression to the screen
*/
void PrintCommand::doCommand(vector<string> args) {
    //if no expression was given, throw exception
    if (args.size() == 0) {
        throw logic_error("no argument to print command");
    }
    //if the expression is a name of a variable
    if (symbolTable->count(args[0]) > 0) {
        cout << symbolTable->find(args[0])->second << endl;
        //else if is a text
    } else {
        //for each word
        for (auto& word : args) {
            //remove the quotation marks from the edges
            if (word[0] == '\"') {
                word.erase(word.begin());
            }
            if (word[word.size() - 1] == '\"') {
                word.erase(word.begin() + (word.size() - 1));
            }
            //print the word
            cout << word << " ";
        }
        cout << endl;
    }
}
