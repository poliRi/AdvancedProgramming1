#include "PrintCommand.h"

PrintCommand::PrintCommand(map<string, double> &symbolTable) {
    this->symbolTable = &symbolTable;
}

void PrintCommand::doCommand(vector<string> args) {
    if (args.size() == 0) {
        throw logic_error("no argument to print command");
    }
    if (symbolTable->count(args[0]) > 0) {
        cout << symbolTable->find(args[0])->second << endl;
    } else {
        for (auto& word : args) {
            if (word[0] == '\"') {
                word.erase(word.begin());
            }
            if (word[word.size() - 1] == '\"') {
                word.erase(word.begin() + (word.size() - 1));
            }
            cout << word << " ";
        }
        cout << endl;
    }
}
