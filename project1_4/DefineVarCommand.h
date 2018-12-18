#include "interface.h"

class DefineVarCommand : public Command {

    private:
        int numOfArgs;

    public:
        DefineVarCommand();
        int doCommand(vector<string> args);
        int getNumOfArgs();

};
