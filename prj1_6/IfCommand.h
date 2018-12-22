#include "interface.h"
#include "ConditionParser.h"
#include "Interpreter.h"

class IfCommand : public Command {

    private:
        ConditionParser* condition;
        map<string, double> symbolTable;

    public:
        IfCommand(map<string, double> symbolTable);
        void setCondition(ConditionParser* condition);
        void doCommand(vector<string> args);
};


