#include "AssignmentCommand.h"

AssignmentCommand::AssignmentCommand(map<string, double> symbolTable) {
    this->symbolTable = symbolTable;
}

void AssignmentCommand::doCommand(vector<string> args) {
    if (symbolTable.count(args[0]) <= 0) {
        throw logic_error("assignment to unrecognized var");
    }
    (symbolTable.find(args[0])->second) = stod(args[1]);
}
