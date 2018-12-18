#include "interface.h"

class OpenServerCommand : public Command {

    private:
        int numOfArgs;

    public:
        OpenServerCommand();
        int doCommand(vector<string> args);
        int getNumOfArgs();
};
