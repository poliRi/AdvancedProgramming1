#include "interface.h"

class DefineVarCommand : public Command {

    private:
        map<string, double> symbolTable;

    public:
        DefineVarCommand();
        void doCommand(vector<string> args);

};
