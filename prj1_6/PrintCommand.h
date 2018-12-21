#include "interface.h"

class PrintCommand : public Command {

    private:
        map<string, double> symbolTable;

    public:
        PrintCommand(map<string, double> symbolTable);
        void doCommand(vector<string> args);
};
