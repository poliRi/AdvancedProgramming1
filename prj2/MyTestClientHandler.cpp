#include "MyTestClientHandler.h"
#include "FileCacheManager.h"

MyTestClientHandler::MyTestClientHandler(Solver* solver, CacheManager* cacheManager) {
    this->solver = solver;
    this->cm = cacheManager;
}

//handles string reverse clients
void MyTestClientHandler::handleClient(int sock) {
    char buffer[1024];
    int n;
    while (true) {
        vector<string> problem = {};
        string row = "";
        string solution = "";
        bzero(buffer, 1024);

        n = read(sock, buffer, 1023);
        if (n < 0) {
            cout << "timeout";
            exit(1);
        }

        for (int i = 0; buffer[i] != '\n'; i++) {
            row += buffer[i];
        }
        //stop when getting "end"
        if (row == "end") {
            break;
        }
        //send solution
        problem.push_back(row);
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

//makes copy of current handler
ClientHandler* MyTestClientHandler::clone() {
    ClientHandler* handler = new MyTestClientHandler(this->solver, this->cm);
    return handler;
}
