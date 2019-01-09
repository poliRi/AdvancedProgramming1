#ifndef _TIMEOUT_H
#define _TIMEOUT_H
#include "interface.h"
#include "ServerSide.h"

using namespace server_side;

class Timeout {

    Server* server;

    public:
        Timeout(Server* server);
        void wait(bool& indicator);
        static void* count(void *arg);
};

#endif // _TIMEOUT_H


