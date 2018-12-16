//
// Created by Polina Rabinovich on 10/12/2018.
//

#ifndef PROJECT1_OPENSERVERCOMMAND_H
#define PROJECT1_OPENSERVERCOMMAND_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "Command.h"

class OpenServerCommand : public Command {
public:
    int execute(string args) {
        // if args.len != 2 throw exeception
    }

};


#endif //PROJECT1_OPENSERVERCOMMAND_H
