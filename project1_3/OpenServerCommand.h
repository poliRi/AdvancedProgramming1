#include "interface.h"

class OpenServerCommand : public Command {

    public:
        OpenServerCommand();
        void doCommand(vector<string> args);
};
