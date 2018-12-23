#include "AssignmentCommand.h"

AssignmentCommand::AssignmentCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

bool AssignmentCommand::isNumber(string s) {
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] != '0')&&(s[i] != '1')&&(s[i] != '2')&&(s[i] != '3')&&(s[i] != '4')&&(s[i] != '5')&&
        (s[i] != '6')&&(s[i] != '7')&&(s[i] != '8')&&(s[i] != '9')&&(s[i] != '.')&&(s[i] != '-')) {
            return false;
        }
    }
    return true;
}

void AssignmentCommand::doCommand(vector<string> args) {
    string destination = args[0];
    string source = args[1];
    if (symbolTable->count(destination) <= 0) {
        throw logic_error("assignment to unrecognized var");
    }
    if (symbolTable->count(source) > 0) {
        (symbolTable->find(destination)->second) = (symbolTable->find(source)->second);
    } else {
        if (!isNumber(source)) {
            throw invalid_argument("assignment to invalid expression");

        }
       (symbolTable->find(destination)->second) = stod(source);
    }
    (pathTable->find(destination)->second) = " ";
}
