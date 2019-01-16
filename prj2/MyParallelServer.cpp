#include "MyParallelServer.h"

MyParallelServer::MyParallelServer() {}

void MyParallelServer::open(int port, ClientHandler* clientHandler) {
    struct parallelServerParams* sp = new parallelServerParams();
    sp->sock = sock;
    sp->port = port;
    sp->handler = clientHandler;
    pthread_t sock;
    pthread_create(&sock, nullptr, createSocket, (void *)sp);
    pthread_join(sock, nullptr);
}

void MyParallelServer::stop() {
    close(sock);
}

void *MyParallelServer::createSocket(void *arg) {
    struct parallelServerParams* sp = (struct parallelServerParams*) arg;
    //socket details declaration
    int sockfd = sp->sock, portno;
    //messages will be holded in the buffer
    struct sockaddr_in serv_addr, cli_addr;

    ClientHandler* handler = sp->handler;

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

    struct ClientCounter* clientCounter = new ClientCounter();
    clientCounter->counter = 0;
    bool isFirstClient = true;
    //start listening for clients
    while (true) {
        listen(sockfd,5);
        socklen_t clilen = sizeof(cli_addr);
        if (!isFirstClient && clientCounter->counter == 0) {
            timeval timeout;
            timeout.tv_sec = 20;
            timeout.tv_usec = 0;

            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
        }
        //accept actual connection from the client
        int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "timeout" << endl;
                exit(2);
            } else {
                perror("ERROR on accept");
                exit(3);
            }
            perror("ERROR on accept");
            exit(3);
        }

        clientCounter->counter++;

        cout << "connection occured" << endl;

        struct conversationParams* cp = new conversationParams();
        cp->clientSock = newsockfd;
        cp->handler = handler->clone();
        cp->clientCounter = clientCounter;
        pthread_t serv;
        pthread_create(&serv, nullptr, &MyParallelServer::servClient, (void *)cp);
        isFirstClient = false;
    }
    delete sp;
    pthread_exit(nullptr);
}

void *MyParallelServer::servClient(void *arg) {
    struct conversationParams* cp = (struct conversationParams*) arg;
    cp->handler->handleClient(cp->clientSock);
    cp->clientCounter->counter--;
    delete cp;
    pthread_exit(nullptr);
}
