#include "MyClientHandler.h"
#include "FileCacheManager.h"

MyClientHandler::MyClientHandler(Solver* solver, CacheManager* cacheManager) {
    this->solver = solver;
    this->cm = cacheManager;
}

//handles the current client
void MyClientHandler::handleClient(int sock) {
    char buffer[1024];
    int n;
    vector<string> problem = {};
    string solution = "";
    //sned and receive loop
    while (true) {
        string row = "";

        bzero(buffer, 1024);

        n = read(sock, buffer, 1023);
        if (n < 0) {
            cout << "timeout";
            exit(1);
        }

        for (int i = 0; buffer[i] != '\n'; i++) {
            row += buffer[i];
        }
        //when getting "end", check for solution and send
        if (row == "end") {
            if (cm->contains(problem)) {
                solution = cm->getSolution(problem);
            } else {
                solution = solver->solve(problem);
                cm->saveSolution(problem, solution);
            }
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

//make a copy of the client handler
ClientHandler* MyClientHandler::clone() {
    ClientHandler* handler = new MyClientHandler(this->solver, this->cm);
    return handler;
}
