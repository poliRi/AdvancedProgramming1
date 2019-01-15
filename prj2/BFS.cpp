#include "BFS.h"

BFS::BFS() {}

string BFS::tracePath(vector<vector<pair<int, int>>> parentIndex, pair<int, int> dest) {
	int row = dest.first;
	int col = dest.second;
	list<pair<int, int>> Path;
	while (!(parentIndex[row][col].first == row && parentIndex[row][col].second == col)) {
		Path.push_front(make_pair(row, col));
		int temp_row = parentIndex[row][col].first;
		int temp_col = parentIndex[row][col].second;
		row = temp_row;
		col = temp_col;
	}
	Path.push_front(make_pair(row, col));
	string path = "";
	int parentRow = Path.front().first;
	int parentCol = Path.front().second;
	list<pair<int, int>>::iterator it = Path.begin();
	it++;
	for (; it != Path.end(); ++it) {
        row = it->first;
        col = it->second;
        if (row < parentRow) {
            path += "Up, ";
        } else if (row > parentRow) {
            path += "Down, ";
        } else if (col < parentCol) {
            path += "Left, ";
        } else if (col > parentCol) {
            path += "Right, ";
        }
        parentRow = it->first;
        parentCol = it->second;
    }
    path.erase(path.end() - 2, path.end());
    return path;
}

string BFS::search(Searchable* area, pair<int, int> source, pair<int, int> destination) {
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
    vector<vector<pair<int, int>>> parentIndex;
	for (int i = 0; i < rows; i++) {
        vector<pair<int, int>> v = {};
		for (int j = 0; j < cols; j++) {
            v.push_back({-1, -1});
		}
		parentIndex.push_back(v);
	}
	// Initialising the parameters of the starting node
	parentIndex[source.first][source.second] = {source.first, source.second};
    Node src = {source.first, source.second, 0};
	// applying BFS on matrix cells starting from source
	queue<Node> q;
	q.push(src);
	visited[src.row][src.col] = true;
	while (!q.empty()) {
		Node p = q.front();
		q.pop();
		// Destination found;
		if (p.row == destination.first && p.col == destination.second) {
			return tracePath(parentIndex, destination);
        }
        int rowDirection[] = {0, 1, 0, -1};
        int colDirection[] = {1, 0, -1, 0};
        for (int k = 0; k < 4; k++) {
            int i = p.row + rowDirection[k];
            int j = p.col + colDirection[k];
            if (area->isValid(i, j) && area->isUnBlocked(i, j) && !visited[i][j]) {
                q.push({i, j, p.dist + matrix[i][j]});
                visited[i][j] = true;
                parentIndex[i][j] = {p.row, p.col};
            }
		}
	}
	return "No possible path found";
}
