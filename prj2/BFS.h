#ifndef _BFS_H
#define _BFS_H
#include "interface.h"

// N x N matrix
#define N 10

class BFS {

    public:
        BFS();
        bool isValid(int x, int y);
        void printPath(vector<pair<int, int>> path);
        int findPath(int matrix[][N], pair<int, int> source, pair<int, int> destination);
};

// queue node used in BFS
struct Node {
	// (x, y) represents coordinates of a cell in matrix
	int x, y;

	// path stores complete path from source cell to cell (x, y)
	vector<pair<int, int>> path;

	// As we are using struct as a key in a std::map,
	// we need to overload below operators

	bool const operator==(const Node& ob) const {
		return x == ob.x && y == ob.y;
	}

	bool operator<(const Node& ob) const {
		return x < ob.x || (x == ob.x && y < ob.y);
	}
};

#endif // _BFS_H
