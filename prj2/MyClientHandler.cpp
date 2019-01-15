#include "MyClientHandler.h"
#include "FileCacheManager.h"

MyClientHandler::MyClientHandler(Solver* solver, CacheManager* cacheManager) {
    this->solver = solver;
    this->cm = cacheManager;
}

void MyClientHandler::handleClient(int sock) {
    char buffer[1024];
    int n;
    string row = "";
    string solution = "";
    vector<string> problem = {};
    while (true) {
        row = "";
        bzero(buffer, 1024);

        n = read(sock, buffer, 1023);
        if (n < 0) {
            cout << "timeout";
            exit(1);
        }

        for (int i = 0; buffer[i] != '\n'; i++) {
            row += buffer[i];
        }

        if (row == "end") {
            /*if (cm->contains(row)) {
                solution = cm->getSolution(row);
            } else {
                solution = solver->solve({row});
                cm->saveSolution(row, solution);
            }*/

            solution = solver->solve(problem);
            strcpy(buffer, solution.c_str());
            n = write(sock, buffer, strlen(buffer));
            break;
        }
        problem.push_back(row);
        n = write(sock, " ", 1);
        if (n < 0) {
            cout << "ERROR writing to socket";
            exit(1);
        }
    }
}
