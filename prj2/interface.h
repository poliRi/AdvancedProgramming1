#ifndef _INTERFACE_H
#define _INTERFACE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include<map>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include<list>
#include <queue>
#include <climits>
#include <errno.h>

using namespace std;

/*
ClientHandler interface. has the handleClient method
*/
class ClientHandler {

    public:
        virtual void handleClient(int sock) = 0;
        virtual ClientHandler* clone() = 0;
};

/*
Solver interface. has the solve method
*/
class Solver {

    public:
        virtual string solve(vector<string> problem) = 0;
};

/*
CacheManager interface. in charge of saving new solutions for different problems,
or loading solutions for problems that are already exist
*/
class CacheManager {

    public:
        virtual bool contains(vector<string> problem) = 0;
        virtual string getSolution(vector<string> problem) = 0;
        virtual void saveSolution(vector<string> problem, string solution) = 0;
};

class Searchable {

    public:
        virtual bool isValid(int row, int col) = 0;
        virtual bool isUnBlocked(int row, int col) = 0;
        virtual vector<vector<int>> getArea() = 0;
        virtual pair<int, int> getSize() = 0;
};

/*
Searcher interface. has the search method
*/
class Searcher {

    public:
        virtual string search(Searchable* area, pair<int, int> source, pair<int, int> destination) = 0;
};

/*
a node for current location and distance from source location
*/
struct Node {
	int row;
	int col;
	int dist;
};

// a node structure used in Astar
struct ANode {
	// f = g + h
	double f;
	int g;
	double h;
	int dist;
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i;
	int parent_j;
};

#endif // _INTERFACE_H
