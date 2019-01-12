#ifndef _GREEDYBFS_H
#define _GREEDYBFS_H
#include "interface.h"

class GreedyBFS : public Searcher {

    public:
        GreedyBFS();
        void sortQueue(vector<vector<int>> matrix, list<Node> &pQueue);
        int search(Searchable* area, pair<int, int> source, pair<int, int> destination);
};

#endif // _GREEDYBFS_H

