#ifndef SLEEPCOMMAND_H
#define SLEEPCOMMAND_H
#include "interface.h"

class SleepCommand : public Command {

    public:
        SleepCommand();
        void doCommand(vector<string> args);

};

#endif // SLEEPCOMMAND_H

