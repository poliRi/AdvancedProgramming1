#ifndef _GREEDYBFS_H
#define _GREEDYBFS_H
#include "interface.h"

class GreedyBFS : public Searcher {

    public:
        GreedyBFS();
        string tracePath(vector<vector<pair<int, int>>> parentIndex, pair<int, int> dest);
        void sortQueue(vector<vector<int>> matrix, list<Node> &pQueue);
        string search(Searchable* area, pair<int, int> source, pair<int, int> destination);
};

#endif // _GREEDYBFS_H

