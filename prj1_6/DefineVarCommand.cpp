#include "DefineVarCommand.h"

DefineVarCommand::DefineVarCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    this->symbolTable = symbolTable;
    this->pathTable = pathTable;
}

void DefineVarCommand::doCommand(vector<string> args) {
    if (symbolTable.count(args[0]) > 0) {
        throw logic_error("redefinition of var");
    } else {
        symbolTable.insert(pair<string,double>(args[0],NULL));
        pathTable.insert(pair<string,string>(args[0]," "));
    }
}
