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

namespace boot {
    Main::Main() {}
    void Main::main(int port) {
        MySerialServer* server = new MySerialServer();
        Solver* solver = new SearcherSolver(new Astar());
        CacheManager* cm = new FileCacheManager("shortest_path");
        ClientHandler* handler = new MyClientHandler(solver, cm);
        server->open(port, handler);
        server->stop();

        /*MySerialServer* server = new MySerialServer();
        Solver* solver = new StringReverser();
        CacheManager* cm = new FileCacheManager("string_reverse");
        ClientHandler* handler = new MyTestClientHandler(solver, cm);
        server->open(port, handler);
        server->stop();*/

        /*MyParallelServer* server = new MyParallelServer();
        Solver* solver = new SearcherSolver(new Astar());
        CacheManager* cm = new FileCacheManager("shortest_path");
        ClientHandler* handler = new MyClientHandler(solver, cm);
        server->open(port, handler);
        server->stop();*/

        /*MyParallelServer* server = new MyParallelServer();
        Solver* solver = new StringReverser();
        CacheManager* cm = new FileCacheManager("string_reverse");
        ClientHandler* handler = new MyTestClientHandler(solver, cm);
        server->open(port, handler);
        server->stop();*/
    }
}
