#include "StringReverser.h"

StringReverser::StringReverser() {}

//string reverses
string StringReverser::solve(vector<string> problem) {
    string result = "";
    for (int i = problem[0].size() - 1; i >= 0; i--) {
        result += problem[0][i];
    }
    return result;
}
