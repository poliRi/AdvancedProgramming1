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

    public:
        WhileCommand(map<string, double> &symbolTable, map<string, string> &pathTable);
        void setCondition(ConditionParser* condition);
        void doCommand(vector<string> args);
};

#endif // WHILECOMMAND_H

