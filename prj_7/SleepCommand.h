#include "interface.h"

class SleepCommand : public Command {

    public:
        SleepCommand();
        void doCommand(vector<string> args);

};

