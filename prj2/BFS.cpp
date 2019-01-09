#include "BFS.h"

BFS::BFS() {}

// The function returns false if pt is not a valid position
bool BFS::isValid(int x, int y) {
	return (x >= 0 && x < N) && (y >= 0 && y < N);
}

// Function to print the complete path from source to destination
void BFS::printPath(vector<pair<int, int>> path) {
	cout << "Destination Found:\t";
	for (pair<int, int> p: path) {
		cout << "(" << p.first << ", " << p.second << ") ";
    }
	cout << endl;
}

// Find shortest route in the matrix from source cell (x, y) to
// destination cell (N - 1, N - 1)
int BFS::findPath(int matrix[][N], pair<int, int> source, pair<int, int> destination) {
	vector<pair<int, int>> path;
	path.push_back({source.first, source.second});

	// create a queue and enqueue first node
	queue<Node> Q;
	Node src = {source.first, source.second, path};
	Q.push(src);

	// map to check if matrix cell is visited before or not
	map<Node, bool> visited;
	visited[src] = true;

	// run till queue is not empty
	while (!Q.empty()) {
		// pop front node from queue and process it
		Node curr = Q.front();
		Q.pop();

		int i = curr.x, j = curr.y;
		path = curr.path;

		// if destination is found, return true
		if (i == destination.first && j == destination.second) {
			printPath(path);
			return path.size() - 1;
		}

		// value of current cell
		int n = matrix[i][j];

		// Below arrays details all 4 possible movements from a cell
        int row[] = { -1, 0, 0, 1 };
        int col[] = { 0, -1, 1, 0 };

		// check all 4 possible movements from current cell
		// and recurse for each valid movement
		for (int k = 0; k < 4; k++) {
			// get next position coordinates using value of current cell
			int x = i + row[k] * n;
			int y = j + col[k] * n;

			// check if it is possible to go to next position
			// from current position
			if (isValid(x, y)) {
				// include next vertex in the path
				path.push_back({x, y});

				// construct next cell node
				Node next = {x, y, path};

				if (!visited.count(next)) {
					Q.push(next);
					visited[next] = true;
				}

				// exclude next vertex in the path
				path.pop_back();
			}
		}
	}
	// return INFINITY if path is not possible
	return INT_MAX;
}
