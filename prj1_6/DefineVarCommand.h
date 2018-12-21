#include "interface.h"

class DefineVarCommand : public Command {

private:
    map<string, double> symbolTable;

public:
    DefineVarCommand(map<string, double> symbolTable);
    void doCommand(vector<string> args);

};
