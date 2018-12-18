#include "DefineVarCommand.h"

DefineVarCommand::DefineVarCommand() {
    this->numOfArgs = 4;
}

int DefineVarCommand::doCommand(vector<string> args) {
    //args.erase(args.begin()+1);
    //args.erase(args.begin()+1);


    return numOfArgs + 1;
}

int DefineVarCommand::getNumOfArgs() {
    return numOfArgs;
}

