#include "FileCacheManager.h"
#include "Utils.h"

//loads data from file
FileCacheManager::FileCacheManager(string problemType) {
    this->fileName = problemType + "_solutions.txt";
    this->solutions = {};
    vector<string> problem = {};
    ifstream reader(fileName);
    if (reader.is_open()) {
        string line;
        while (getline(reader,line)) {
            if (line == "|") {
                getline(reader,line);
                this->solutions.insert(pair<vector<string>,string>(problem, line));
                problem.clear();
                getline(reader,line);
                getline(reader,line);
            }
            problem.push_back(line);
        }
    }
    reader.close();
}

//checks if contains the solution
bool FileCacheManager::contains(vector<string> problem) {
    return solutions.find(problem) != solutions.end();
}

//returns solution
string FileCacheManager::getSolution(vector<string> problem) {
    return solutions.find(problem)->second;
}

//saves solution to file
void FileCacheManager::saveSolution(vector<string> problem, string solution) {
    solutions.insert(pair<vector<string>,string>(problem, solution));
    ofstream writer(fileName, writer.app);
    if (writer.is_open()) {
        for (auto& line : problem) {
            writer << line << endl;
        }
        writer << "|" << endl << solution << endl << endl;
    } else {
        cerr << "error opening file" << endl;
    }
    writer.close();
}
