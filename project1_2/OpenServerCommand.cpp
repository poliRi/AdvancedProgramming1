#include "OpenServerCommand.h"

OpenServerCommand::OpenServerCommand() {

}
void OpenServerCommand::doCommand(vector<string> args) {
    // if args.len != 2 throw exeception
    if (args.size()!= 2) {
        throw std::invalid_argument( "invalid argument" );
    } else {
        //send two parameters to Data Reader Server
    }
}
