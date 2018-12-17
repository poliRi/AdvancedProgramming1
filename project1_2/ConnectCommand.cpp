#include "ConnectCommand.h"

ConnectCommand::ConnectCommand() {

}

void ConnectCommand::doCommand(vector<string> args) {
    // if args.len != 2 throw exeception
    if (args.size() != 2) {
        throw invalid_argument("invalid argument");
    } else {
        //send two parameters to Data Reader Server
    }
}


