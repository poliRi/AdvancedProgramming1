#include "interface.h"

class PrintCommand : public Command {

    private:
        int numOfArgs;

    public:
        PrintCommand();
        int doCommand(vector<string> args);
        int getNumOfArgs();

};

