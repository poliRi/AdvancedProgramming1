#include "interface.h"

class AssignmentCommand : public Command {

    private:
        map<string, double> symbolTable;

    public:
        AssignmentCommand(map<string, double> symbolTable);
        void doCommand(vector<string> args);
};
