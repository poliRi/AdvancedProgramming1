#ifndef _FILECACHEMANAGER_H
#define _FILECACHEMANAGER_H
#include "interface.h"

class FileCacheManager : public CacheManager {

    map<string, string> solutions;
    string fileName;

    public:
        FileCacheManager(string problemType);
        bool contains(string problem);
        string getSolution(string problem);
        void saveSolution(string problem, string solution);
};

#endif // _FILECACHEMANAGER_H

