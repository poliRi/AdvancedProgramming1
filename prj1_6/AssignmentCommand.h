#ifndef ASSIGNMENTCOMMAND_H
#define ASSIGNMENTCOMMAND_H
#include "interface.h"

class AssignmentCommand : public Command {

    private:
        map<string, double> *symbolTable;
        map<string, string> *pathTable;

    public:
        AssignmentCommand(map<string, double> &symbolTable, map<string, string> &pathTable);
        bool isNumber(string s);
        void doCommand(vector<string> args);
};

#endif // ASSIGNMENTCOMMAND_H
