#ifndef _MYPARALLELSERVER_H
#define _MYPARALLELSERVER_H
#include "interface.h"
#include "ServerSide.h"

using namespace server_side;

class MyParallelServer : public Server {

    int sock;

    public:
        MyParallelServer();
        void open(int port, ClientHandler* clientHandler);
        void stop();
        static void* createSocket(void *arg);
        static void* servClient(void *arg);
};

struct parallelServerParams {
    int sock;
    int port;
    ClientHandler* handler;
};

struct ClientCounter {
    int counter;
};

struct conversationParams {
    int clientSock;
    ClientHandler* handler;
    ClientCounter* clientCounter;
};

#endif // _MYPARALLELSERVER_H

