#include "PrintCommand.h"

PrintCommand::PrintCommand() {
    this->numOfArgs = 1;
}

int PrintCommand::doCommand(vector<string> args) {
    cout << args[0] << endl;
    return numOfArgs + 1;
}

int PrintCommand::getNumOfArgs() {
    return numOfArgs;
}


