#include "ConnectCommand.h"
#include "Utils.h"
#include "Client.h"


ConnectCommand::ConnectCommand() {}

void ConnectCommand::doCommand(vector<string> args) {
    // if args.len != 2 throw exeception
    if (args.size()!= 2) {
        throw invalid_argument("invalid number of arguments");
    } else {
        string ip = args[0];
        int port =  stoi(args[1]);
        vector<string> numbers = Utils::Split(args[0], ".");
        if (numbers.size()!=4) {
           throw invalid_argument("invalid ip address");
        } else {
            for (int i = 0; i < 4; i++) {
                int num = stoi(numbers[i]);
                if ((num<0)||(num>255)) {
                   throw invalid_argument("invalid ip address");
                }
            }
        }
        if (port<0) {
           throw invalid_argument("invalid port number");
        }
        Client client(ip, port);
        client.connectToServer();
    }
}
