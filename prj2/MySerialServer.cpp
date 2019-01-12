#include "MySerialServer.h"
#include "Timeout.h"

MySerialServer::MySerialServer() {}

void MySerialServer::open(int port, ClientHandler* clientHandler) {
    struct serverParams* sp = new serverParams();
    sp->sock = sock;
    sp->clientSock = clientSock;
    sp->port = port;
    sp->handler = clientHandler;
    sp->timeout = new Timeout(this);
    pthread_t sock;
    pthread_create(&sock, nullptr, createSocket, (void *)sp);
    pthread_join(sock, nullptr);
}

void MySerialServer::stop() {
    close(clientSock);
    close(sock);
}

void *MySerialServer::createSocket(void *arg) {
    struct serverParams* sp = (struct serverParams*) arg;
    //socket details declaration
    int sockfd = sp->sock, newsockfd = sp->clientSock, portno, clilen;
    //messages will be holded in the buffer
    struct sockaddr_in serv_addr, cli_addr;

    ClientHandler* handler = sp->handler;
    Timeout* timeout = sp->timeout;

    //first call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout <<"ERROR opening socket";
        exit(1);
    }

    //initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = sp->port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //now bind the host address using bind() call
    if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cout << "ERROR on binding";
        exit(1);
    }

    //start listening for clients
    while (true) {
        //bool isConnected = false;
        //timeout->wait(isConnected);
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        //accept actual connection from the client
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
        if (newsockfd < 0) {
            cout << "ERROR on accept";
            exit(1);
        }

        //isConnected = true;

        cout << "connection occured" << endl;
        handler->handleClient(newsockfd);
    }
    delete sp;
    pthread_exit(nullptr);
}
