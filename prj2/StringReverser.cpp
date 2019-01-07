#include "StringReverser.h"

StringReverser::StringReverser() {}

string StringReverser::solve(string problem) {
    string result = "";
    for (int i = problem.size() - 1; i >= 0; i--) {
        result += problem[i];
    }
    return result;
}
