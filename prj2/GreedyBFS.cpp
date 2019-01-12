#include "GreedyBFS.h"

GreedyBFS::GreedyBFS() {}

void GreedyBFS::sortQueue(vector<vector<int>> matrix, list<Node> &pQueue) {
    int n = pQueue.size();
    Node arr[n];
    int i = 0, j;
    for (auto node : pQueue) {
        arr[i] = node;
        i++;
    }
    pQueue.clear();
    Node key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i-1;

        /* Move elements of arr[0..i-1], that are
            greater than key, to one position ahead
            of their current position */
        while (j >= 0 && matrix[arr[j].row][arr[j].col] > matrix[key.row][key.col]) {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
    for (i = 0; i < n; i++) {
        pQueue.push_back(arr[i]);
    }
}

int GreedyBFS::search(Searchable* area, pair<int, int> source, pair<int, int> destination) {
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
	list<Node> pQueue;
	pQueue.push_front(src);
	visited[src.row][src.col] = true;
	while (!pQueue.empty()) {
        sortQueue(matrix, pQueue);
		Node p = pQueue.front();
        pQueue.pop_front();

		// Destination found;
		if (p.row == destination.first && p.col == destination.second) {
			return p.dist;
        }

        int rowDirection[] = {0, 1, 0, -1};
        int colDirection[] = {1, 0, -1, 0};

        for (int k = 0; k < 4; k++) {
            int i = p.row + rowDirection[k];
            int j = p.col + colDirection[k];
            if (area->isValid(i, j) && area->isUnBlocked(i, j) && !visited[i][j]) {
                pQueue.push_back({i, j, p.dist + matrix[i][j]});
                visited[i][j] = true;
            }
		}
	}
	return -1;
}

