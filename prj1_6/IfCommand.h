#ifndef IFCOMMAND_H
#define IFCOMMAND_H
#include "interface.h"
#include "ConditionParser.h"
#include "Interpreter.h"

class IfCommand : public Command {

    private:
        ConditionParser* condition;
        map<string, double> *symbolTable;
        map<string, string> *pathTable;

    public:
        IfCommand(map<string, double> &symbolTable, map<string, string> &pathTable);
        void setCondition(ConditionParser* condition);
        void doCommand(vector<string> args);
};

#endif // IFCOMMAND_H


