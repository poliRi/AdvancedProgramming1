#ifndef _MYSERIALSERVER_H
#define _MYSERIALSERVER_H
#include "interface.h"
#include "ServerSide.h"

using namespace server_side;

class MySerialServer : public Server {

    public:
        MySerialServer();
        void open(int port, ClientHandler* clientHandler);
        void serv();
        void stop();
        static void* createSocket(void *arg);
};

struct serverParams {
    int port;
    ClientHandler* handler;
};

#endif // _MYSERIALSERVER_H
