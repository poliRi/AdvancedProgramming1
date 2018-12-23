#include "AssignmentCommand.h"

AssignmentCommand::AssignmentCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    this->symbolTable = symbolTable;
    this->pathTable = pathTable;
}

bool AssignmentCommand::isDigit(char c) {
    return ((c == '0')||(c == '1')||(c == '2')||(c == '3')||(c == '4')||(c == '5')||(c == '6')||
    (c == '7')||(c == '8')||(c == '9'));
}

void AssignmentCommand::doCommand(vector<string> args) {
    string destination = args[0];
    string source = args[1];
    if (symbolTable.count(destination) <= 0) {
        throw logic_error("assignment to unrecognized var");
    }
    if (symbolTable.count(source) > 0) {
        (symbolTable.find(destination)->second) = (symbolTable.find(source)->second);
    } else {
        for (int i = 0; i < source.size(); i++) {
            if (!isDigit(source[i])) {
                throw invalid_argument("assignment to invalid expression");

            }
        }
       (symbolTable.find(destination)->second) = stod(source);
    }
    (pathTable.find(destination)->second) = " ";
}
