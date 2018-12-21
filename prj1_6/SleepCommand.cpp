#include "SleepCommand.h"

SleepCommand::SleepCommand() {}

void SleepCommand::doCommand(vector<string> args) {
    int milliSeconds = stoi(args[0]);
    usleep(milliSeconds);
}

