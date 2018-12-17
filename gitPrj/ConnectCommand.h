//
// Created by Polina Rabinovich on 17/12/2018.
//

#ifndef PROJECT1_CONNECTCOMMAND_H
#define PROJECT1_CONNECTCOMMAND_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "Command.h"
#include <vector>


class ConnectCommand {

private:

public:

    void doCommand(vector<string> args) {
        // if args.len != 2 throw exeception
        if (args.size() != 2) {
            throw std::invalid_argument("invalid argument");
        } else {
            //send two parameters to Data Reader Server
        }
    }

};


#endif //PROJECT1_CONNECTCOMMAND_H
