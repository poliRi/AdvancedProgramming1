#ifndef IFCOMMAND_H
#define IFCOMMAND_H
#include "interface.h"
#include "ConditionParser.h"
#include "Interpreter.h"

/*
class IfCommand represents an if condition
*/
class IfCommand : public Command {

    private:
        ConditionParser* condition;
        map<string, double> *symbolTable;
        map<string, string> *pathTable;
        map<string, bool> *isAssigned;

    public:
        IfCommand(map<string, double> &symbolTable, map<string, string> &pathTable,
        map<string, bool> &isAssigned);
        void setCondition(ConditionParser* condition);
        void doCommand(vector<string> args);
};

#endif // IFCOMMAND_H


