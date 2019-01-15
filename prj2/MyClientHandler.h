#ifndef _MYCLIENTHANDLER_H
#define _MYCLIENTHANDLER_H
#include "interface.h"

class MyClientHandler : public ClientHandler {

    Solver* solver;
    CacheManager* cm;

    public:
        MyClientHandler(Solver* solver, CacheManager* cacheManager);
        void handleClient(int sock);
};

#endif // _MYCLIENTHANDLER_H
