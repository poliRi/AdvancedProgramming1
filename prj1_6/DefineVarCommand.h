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
        map<string, bool> *isAssigned;

    public:
        DefineVarCommand(map<string, double> &symbolTable, map<string, string> &pathTable,
        map<string, bool> &isAssigned);
        void doCommand(vector<string> args);
        bool isDigit(char c);
        bool isLetter(char c);

};

#endif // DEFINEVARCOMMAND_H
