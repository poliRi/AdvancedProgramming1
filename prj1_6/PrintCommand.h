#include "interface.h"

class PrintCommand : public Command {

    public:
        PrintCommand();
        void doCommand(vector<string> args);

};

