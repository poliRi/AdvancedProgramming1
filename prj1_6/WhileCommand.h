#include "interface.h"
#include "ConditionParser.h"
#include "Interpreter.h"

class WhileCommand : public Command {

    private:
        ConditionParser* condition;
        map<string, double> symbolTable;

    public:
        WhileCommand(map<string, double> symbolTable);
        void setCondition(ConditionParser* condition);
        void doCommand(vector<string> args);
};

