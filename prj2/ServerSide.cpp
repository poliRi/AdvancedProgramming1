#include "ServerSide.h"
#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "BFS.h"
#include "Astar.h"

namespace boot {
    Main::Main() {}
    void Main::main(int port) {
        int matrix[N][N] = {
            { 4, 4, 6, 5, 5, 1, 1, 1, 7, 4 },
            { 3, 6, 2, 4, 6, 5, 7, 2, 6, 6 },
            { 1, 3, 6, 1, 1, 1, 7, 1, 4, 5 },
            { 7, 5, 6, 3, 1, 3, 3, 1, 1, 7 },
            { 3, 4, 6, 4, 7, 2, 6, 5, 4, 4 },
            { 3, 2, 5, 1, 2, 5, 1, 2, 3, 4 },
            { 4, 2, 2, 2, 5, 2, 3, 7, 7, 3 },
            { 7, 2, 4, 3, 5, 2, 2, 3, 6, 3 },
            { 5, 1, 4, 2, 6, 4, 6, 7, 3, 7 },
            { 1, 4, 1, 7, 5, 3, 6, 5, 3, 4 }
        };
        BFS* bfs = new BFS();
        // Find a route in the matrix from source cell (0, 0) to
        // destination cell (N - 1, N - 1)
        int len = bfs->findPath(matrix, {0, 0}, {N - 1, N - 1});
        if (len != INT_MAX) {
            cout << "Shortest Path length is " << len << endl;
        }

        /* Description of the Grid-
        1--> The cell is not blocked
        0--> The cell is blocked */
        int grid[ROW][COL] = {
            { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
        };
        Astar* astar = new Astar();
        astar->aStarSearch(grid, {0, 0}, {0, 9});

        MySerialServer* server = new MySerialServer();
        Solver* solver = new StringReverser();
        CacheManager* cm = new FileCacheManager();
        ClientHandler* handler = new MyTestClientHandler(solver, cm);
        server->open(port, handler);
        server->stop();
    }
}
