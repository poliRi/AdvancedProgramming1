#include "Utils.h"

Utils::Utils() {

}
//split string by delimeter
vector<string> Utils::Split(string str, string delimeter) {
    ifstream myfile;
    vector<string> tokens;
    size_t pos;


    while (pos = str.find(delimeter)) {
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
        //if line.find() doesn't find delimiter, it returns npos
        if (pos == string::npos) {
            break;
        }
    }
    return tokens;
}
//split file by delimeter
vector<string> Utils::Split(ifstream  &file, string delimeter) {

    vector<string> tokens;

    string line;

    while (getline(file, line)) {
        size_t pos = 0;
        string token;

        while (pos = line.find(delimeter)) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
            //if line.find() doesn't find delimiter, it returns npos
            if (pos == string::npos) {
                break;
            }
        }

    }
    return tokens;
}
