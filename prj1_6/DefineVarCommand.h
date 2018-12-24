#ifndef DEFINEVARCOMMAND_H
#define DEFINEVARCOMMAND_H
#include "interface.h"

/*
class DefineVarCommand is in charge of defining a new variable
in the program and adding it to the main symbol tables
*/
class DefineVarCommand : public Command {

    private:
        map<string, double> *symbolTable;
        map<string, string> *pathTable;


    public:
        DefineVarCommand(map<string, double> &symbolTable, map<string, string> &pathTable);
        void doCommand(vector<string> args);

};

#endif // DEFINEVARCOMMAND_H
