#ifndef _MYTESTCLIENTHANDLER_H
#define _MYTESTCLIENTHANDLER_H
#include "interface.h"

class MyTestClientHandler : public ClientHandler {

    Solver* solver;
    CacheManager* cm;

    public:
        MyTestClientHandler(Solver* solver, CacheManager* cacheManager);
        void handleClient(int sock);
};

#endif // _MYTESTCLIENTHANDLER_H
