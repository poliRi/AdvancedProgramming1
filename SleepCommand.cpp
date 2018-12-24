#include "SleepCommand.h"

/*
SleepCommand: constructor
*/
SleepCommand::SleepCommand() {}

/*
sleeps for the number of milliseconds was given
*/
void SleepCommand::doCommand(vector<string> args) {
    //throw exception in case of invalid argument
    if (args.size() == 0) {
        throw logic_error("no argument to sleep command");
    }
    int milliSeconds = stoi(args[0]);
    usleep(milliSeconds);
}

