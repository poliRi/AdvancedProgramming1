#ifndef ASSIGNMENTCOMMAND_H
#define ASSIGNMENTCOMMAND_H
#include "interface.h"

/*
class AssignmentCommand is in charge of assigning a given value to a given variable
*/
class AssignmentCommand : public Command {

    private:
        map<string, double> *symbolTable;
        map<string, string> *pathTable;
        map<string, bool> *isAssigned;

    public:
        AssignmentCommand(map<string, double> &symbolTable, map<string, string> &pathTable,
        map<string, bool> &isAssigned);
        bool isNumber(string s);
        void doCommand(vector<string> args);
};

#endif // ASSIGNMENTCOMMAND_H
