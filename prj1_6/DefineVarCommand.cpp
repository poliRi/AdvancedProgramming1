#include "DefineVarCommand.h"

DefineVarCommand::DefineVarCommand(map<string, double> symbolTable) {
    this->symbolTable = symbolTable;
}

void DefineVarCommand::doCommand(vector<string> args) {
    if (symbolTable.count(args[0]) > 0) {
        throw logic_error("redefinition of var");
    } else {
        symbolTable.insert(pair<string,double>(args[0],NULL));
    }
}
