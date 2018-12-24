#include "DefineVarCommand.h"

/*
DefineVarCommand: constructor
*/
DefineVarCommand::DefineVarCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    //hold a reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

/*
in charge of defining a new variable in the program
*/
void DefineVarCommand::doCommand(vector<string> args) {
    //throw exception if the var is declared twice
    if (symbolTable->count(args[0]) > 0) {
        throw logic_error("redefinition of var");
    } else {
        //insert initialized values to the tables
        symbolTable->insert(pair<string,double>(args[0],0));
        pathTable->insert(pair<string,string>(args[0]," "));
    }
}
