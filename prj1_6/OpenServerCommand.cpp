#include "OpenServerCommand.h"

OpenServerCommand::OpenServerCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

void OpenServerCommand::doCommand(vector<string> args) {
    // if args.len != 2 throw exeception
    if (args.size() != 2) {
        throw invalid_argument("invalid number of arguments");
    } else {
        int port = stoi(args[0]);
        int rate = stoi(args[1]);
        if ((port < 0) || (rate < 0)) {
            throw invalid_argument("invalid argument");
        }

        //pointer to function for pthread
        void *(*doServer)(void *);
        //struct for function
        MyParams *params = new MyParams();
        params->port = port;
        params->rate = rate;
        pthread_t serv;
        pthread_create(&serv, nullptr, doServer, &params);
    }
}

void *OpenServerCommand::doServer(void *arg) {
    //down casting
    MyParams *params = (MyParams *) arg;
    int sockfd, newsockfd, portno, clilen, rate;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    rate = (params->rate) / 100;

    //First call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "ERROR opening socket";
        exit(1);
    }

    //Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = params->port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //Now bind the host address using bind() call
//    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//        cout << "ERROR on binding";
//        exit(1);
//    }



    /* Now start listening for the clients, here process will
        go in sleep mode and will wait for the incoming connection
    */
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    //Accept actual connection from the client
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (newsockfd < 0) {
        cout << "ERROR on accept";
        exit(1);
    }

    //If connection is established then start communicating
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) {
        cout << "ERROR reading from socket";
        exit(1);
    }

    //when we see word "quit"
    while (!strcmp(buffer, "quit")) {
        cout << "Here is the message: " << buffer;

        //Write a response to the client
        n = write(newsockfd, "I got your message", 18);
        if (n < 0) {
            cout << "ERROR writing to socket";
            exit(1);
        }

        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            cout << "ERROR reading from socket";
            exit(1);
        }
        usleep(rate);
    }
}
