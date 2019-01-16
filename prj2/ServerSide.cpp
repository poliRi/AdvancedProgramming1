#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "BFS.h"
#include "DFS.h"
#include "Astar.h"
#include "GreedyBFS.h"
#include "Matrix.h"
#include "SearcherSolver.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"

// boot namespace. includes main function
namespace boot {
    Main::Main() {}
    void Main::main(int port) {
        MySerialServer* server = new MySerialServer();
        Solver* solver = new SearcherSolver(new Astar());
        CacheManager* cm = new FileCacheManager("shortest_path");
        ClientHandler* handler = new MyClientHandler(solver, cm);
        server->open(port, handler);
        server->stop();
    }
}
