//
// Created by Polina Rabinovich on 16/12/2018.
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

class ConnectCommand : public Command {
public:
    int execute(string args) {
        // TODO: seperate args by delimiter (" "), add thread
        int server_fd, new_socket, valread;
        struct sockaddr_in address;

        int addrlen = sizeof(address);
        char buffer[1024] = {0};
        char *hello = "Hello from server";

        // Creating socket file descriptor
        server_fd = socket(AF_INET, SOCK_STREAM, 0);

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(5400);  // TODO: Parse from args

        // Forcefully attaching socket to the port 8080
        connect(server_fd, (struct sockaddr *) &address, sizeof(address));

        listen(server_fd, 5);

        // avvepting a client
        new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t * ) & addrlen);

        valread = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);
        send(new_socket, hello, strlen(hello), 0);
        printf("Hello message sent\n");
        return 0;
    }
};


#endif //PROJECT1_CONNECTCOMMAND_H
