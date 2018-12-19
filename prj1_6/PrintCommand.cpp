#include "PrintCommand.h"

PrintCommand::PrintCommand() {}

void PrintCommand::doCommand(vector<string> args) {
    cout << args[0] << endl;
}


