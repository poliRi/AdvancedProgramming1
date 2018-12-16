//
// Created by Polina Rabinovich on 16/12/2018.
//

#ifndef PROJECT1_DEFINEVARCOMMAND_H
#define PROJECT1_DEFINEVARCOMMAND_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "Command.h"

class DefineVarCommand : public Command {
public:
    int execute(string args);


    };


#endif //PROJECT1_DEFINEVARCOMMAND_H
