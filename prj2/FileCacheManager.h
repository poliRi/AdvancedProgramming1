#ifndef _FILECACHEMANAGER_H
#define _FILECACHEMANAGER_H
#include "interface.h"

class FileCacheManager : public CacheManager {

    map<vector<string>, string> solutions;
    string fileName;

    public:
        FileCacheManager(string problemType);
        bool contains(vector<string> problem);
        string getSolution(vector<string> problem);
        void saveSolution(vector<string> problem, string solution);
};

#endif // _FILECACHEMANAGER_H

