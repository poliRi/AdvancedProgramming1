#ifndef WHILECOMMAND_H
#define WHILECOMMAND_H
#include "interface.h"
#include "ConditionParser.h"
#include "Interpreter.h"

/*
class WhileCommand represents a while condition
*/
class WhileCommand : public Command {

    private:
        ConditionParser* condition;
        map<string, double> *symbolTable;
        map<string, string> *pathTable;
        map<string, bool> *isAssigned;

    public:
        WhileCommand(map<string, double> &symbolTable, map<string, string> &pathTable,
        map<string, bool> &isAssigned);
        void setCondition(ConditionParser* condition);
        void doCommand(vector<string> args);
};

#endif // WHILECOMMAND_H

