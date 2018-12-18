#include "interface.h"

class ConnectCommand : public Command {

    public:
        ConnectCommand();
        void doCommand(vector<string> args);
};
