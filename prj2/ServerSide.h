#ifndef _SERVERSIDE_H
#define _SERVERSIDE_H
#include "interface.h"

//server side namespace. includes server interface
namespace server_side {
    class Server {

        public:
            virtual void open(int port, ClientHandler* clientHandler) = 0;
            virtual void stop() = 0;
    };

}

namespace boot {
    class Main {

        public:
            Main();
            void main(int port);
    };
}

#endif // _SERVERSIDE_H
