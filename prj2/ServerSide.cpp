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
#include "SearcherSolver.h"
#include "MyClientHandler.h"

namespace boot {
    Main::Main() {}
    void Main::main(int port) {
        vector<vector<int>> v{
            { 2, X, 2, 2, 2, 2, 2, 2, 2, 2 },
            { 2, 9, 2, X, 2, 2, 2, X, 2, 2 },
            { 9, 9, 2, X, 2, 2, X, 2, X, 2 },
            { X, X, 2, X, 2, X, X, X, 9, 2 },
            { 2, 2, 2, X, 2, 2, 2, X, 2, X },
            { 2, X, 2, 9, X, X, X, 2, 9, X },
            { 9, X, X, X, X, 2, X, X, 9, 2 },
            { 9, X, 2, 2, 2, 9, X, 9, 9, 2 },
            { 9, X, 2, 9, 2, 2, 2, 2, 2, 2 },
            { 9, 2, 2, X, X, X, 2, X, 2, 2 }
        };
        Searchable* matrix = new Matrix(v);

        Searcher* bfs = new BFS();
        string path = bfs->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << path << endl;

        Searcher* aStar = new Astar();
        path = aStar->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << path << endl;


        Searcher* dfs = new DFS();
        path = dfs->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << path << endl;

        Searcher* greedyBFS = new GreedyBFS();
        path = greedyBFS->search(matrix, {0, 0}, {ROW - 1, COL - 1});
        cout << path << endl;

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
    }
}
