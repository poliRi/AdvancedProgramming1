#include <utility>

#include <iostream>
#include "client.h"
#include "Client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <cstdlib>

#define BUFFER 50

using namespace std;



Client::~Client() {
    close(clientSocket_);
}

void Client::connectToServer() {
    // Create a socket point
    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket_ == -1) {
        throw "Error opening socket";
    }

    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP_.c_str(), &address)) {
        throw "Can't parse IP address. IP is probably in wrong format.";
    }

    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable. Server may be offline.";
    }

    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr,
           server->h_addr,
           server->h_length);

    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort_);

    // Establish a connection with the TCP server
    if (connect(clientSocket_, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
}


int Client::getClientSocket_() const {
    return clientSocket_;
}

Client::Client(string serverIP, int serverPort) {
    this->serverIP_=serverIP;
    this->serverPort_=serverPort;

}
