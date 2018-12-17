//
// Created by Polina Rabinovich on 16/12/2018.
//

#ifndef PROJECT1_UTILS_H
#define PROJECT1_UTILS_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

 class Utils {
 public:
     //split string by delimeter
    static vector<string> split(string str, string delimeter) {
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
    static vector<string> split(ifstream  &file, string delimeter) {

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


};


#endif //PROJECT1_UTILS_H
