#ifndef _SERVERSIDE_H
#define _SERVERSIDE_H
#include "interface.h"

namespace server_side {
    class Server {

        public:
            virtual void open(int port, ClientHandler* clientHandler) = 0;
            virtual void serv() = 0;
            virtual void stop() = 0;
    };

}

namespace boot {
    class Main {

        public:
            int main(int argc, char *argv[]);
    };
}

#endif // _SERVERSIDE_H
