#include "OpenServerCommand.h"

OpenServerCommand::OpenServerCommand() {

}
void OpenServerCommand::doCommand(vector<string> args) {
    // if args.len != 2 throw exeception
    if (args.size()!= 2) {
        throw invalid_argument( "invalid number of arguments" );
    } else {
        int port = stoi(args[0]);
        int rate = stoi(args[1]);
        if ((port<0)||(rate<0)) {
           throw invalid_argument( "invalid argument" );
        }
        //send two parameters to Data Reader Server
    }
}
