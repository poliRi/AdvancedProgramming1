#include "MyTestClientHandler.h"
#include "FileCacheManager.h"

MyTestClientHandler::MyTestClientHandler(Solver* solver, CacheManager* cacheManager) {
    this->solver = solver;
    this->cm = cacheManager;
}

void MyTestClientHandler::handleClient(int sock) {
    char buffer[1024];
    int n;
    string problem;
    string solution;

    while (strcmp(buffer, "end") != 0) {
        bzero(buffer, 1024);

        n = read(sock, buffer, 1023);
        if (n < 0) {
            cout << "ERROR reading from socket";
            exit(1);
        }

        problem = string(buffer);
        if (cm->contains(problem)) {
            solution = cm->getSolution(problem);
        } else {
            solution = solver->solve(problem);
            cm->saveSolution(problem, solution);
        }
        strcpy(buffer, solution.c_str());

        n = write(sock, buffer, strlen(buffer));
        if (n < 0) {
            cout << "ERROR writing to socket";
            exit(1);
        }
    }
}
