#include "interface.h"

class ConnectCommand : public Command {

    private:
        int numOfArgs;

    public:
        ConnectCommand();
        int doCommand(vector<string> args);
        int getNumOfArgs();
};
