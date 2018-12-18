#include "OpenServerCommand.h"

OpenServerCommand::OpenServerCommand() {
    this->numOfArgs = 2;
}
int OpenServerCommand::doCommand(vector<string> args) {
    int port = stoi(args[0]);
    int rate = stoi(args[1]);
    if ((port<0)||(rate<0)) {
       throw invalid_argument("invalid argument");
    }
    //send two parameters to Data Reader Server


    return numOfArgs + 1;
}

int OpenServerCommand::getNumOfArgs() {
    return numOfArgs;
}
