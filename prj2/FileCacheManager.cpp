#include "FileCacheManager.h"
#include "Utils.h"

FileCacheManager::FileCacheManager(string problemType) {
    this->fileName = problemType + "_solutions.txt";
    this->solutions = {};
    vector<string> v = {};
    ifstream reader(fileName);
    if (reader.is_open()) {
        string line;
        while (getline(reader,line)) {
           v = Utils::Split(line, "|");
           this->solutions.insert(pair<string,string>(v[0], v[1]));
        }
    }
    reader.close();
}

bool FileCacheManager::contains(string problem) {
    return solutions.find(problem) != solutions.end();
}

string FileCacheManager::getSolution(string problem) {
    return solutions.find(problem)->second;
}

void FileCacheManager::saveSolution(string problem, string solution) {
    solutions.insert(pair<string,string>(problem, solution));
    ofstream writer(fileName, writer.app);
    if (writer.is_open()) {
        writer << problem << "|" << solution << endl;
    } else {
        cerr << "error opening file" << endl;
    }
    writer.close();
}
