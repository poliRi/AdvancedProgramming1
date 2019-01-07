#include "ServerSide.h"
#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"

namespace boot {
    int Main::main(int argc, char *argv[]) {
        server_side::Server* server = new MySerialServer();
        Solver* solver = new StringReverser();
        CacheManager* cm = new FileCacheManager();
        ClientHandler* handler = new MyTestClientHandler(solver, cm);
        server->open(stoi(argv[0]), handler);

        return 0;
    }
}
