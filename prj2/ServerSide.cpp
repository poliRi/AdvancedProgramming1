#include "ServerSide.h"
#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "BFS.h"
#include "DFS.h"
#include "Astar.h"
#include "GreedyBFS.h"
#include "Matrix.h"

namespace boot {
    Main::Main() {}
    void Main::main(int port) {
        vector<vector<int>> v{
            { 1, X, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 9, 1, X, 1, 1, 1, X, 1, 1 },
            { 9, 9, 1, X, 1, 1, X, 1, X, 1 },
            { X, X, 1, X, 1, X, X, X, 9, 1 },
            { 1, 1, 1, X, 1, 1, 1, X, 1, X },
            { 1, X, 1, 9, X, X, X, 1, 9, X },
            { 9, X, X, X, X, 1, X, X, 9, 1 },
            { 9, X, 1, 1, 1, 9, X, 9, 9, 1 },
            { 9, X, 1, 9, 1, 1, 1, 1, 1, 1 },
            { 9, 1, 1, X, X, X, 1, X, X, 1 }
        };
        Searchable* matrix = new Matrix(v);

        Searcher* bfs = new BFS();
        int len = bfs->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << len << endl;

        Searcher* aStar = new Astar();
        len = aStar->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << len << endl;


        Searcher* dfs = new DFS();
        len = dfs->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << len << endl;

        Searcher* greedyBFS = new GreedyBFS();
        len = greedyBFS->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << len << endl;

        MySerialServer* server = new MySerialServer();
        Solver* solver = new StringReverser();
        CacheManager* cm = new FileCacheManager();
        ClientHandler* handler = new MyTestClientHandler(solver, cm);
        server->open(port, handler);
        server->stop();
    }
}
