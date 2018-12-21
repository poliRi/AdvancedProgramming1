#include "SleepCommand.h"

SleepCommand::SleepCommand() {}

void SleepCommand::doCommand(vector<string> args) {
    if (args.size() == 0) {
        throw logic_error("no argument to sleep command");
    }
    int milliSeconds = stoi(args[0]);
    usleep(milliSeconds);
}

