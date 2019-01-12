#include "DFS.h"

DFS::DFS() {}

int DFS::search(Searchable* area, pair<int, int> source, pair<int, int> destination) {
    vector<vector<int>> matrix = area->getArea();
    // To keep track of visited QItems. Marking
    // blocked cells as visited.
    int rows = area->getSize().first;
    int cols = area->getSize().second;
    bool visited[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
        }
    }

    Node src = {source.first, source.second, 0};

	// applying BFS on matrix cells starting from source
	stack<Node> s;
	s.push(src);
	visited[src.row][src.col] = true;
	while (!s.empty()) {
		Node p = s.top();

		// Destination found;
		if (p.row == destination.first && p.col == destination.second) {
			return p.dist;
        }

        int rowDirection[] = {0, 1, 0, -1};
        int colDirection[] = {1, 0, -1, 0};
        bool visitedAllAdj = true;
        for (int k = 0; k < 4; k++) {
            int i = p.row + rowDirection[k];
            int j = p.col + colDirection[k];
            if (area->isValid(i, j) && area->isUnBlocked(i, j) && !visited[i][j]) {
                s.push({i, j, p.dist + matrix[i][j]});
                visited[i][j] = true;
                visitedAllAdj = false;
                break;
            }
		}
		if (visitedAllAdj) {
            s.pop();
		}
	}
	return -1;
}
