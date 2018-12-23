#include "BindCommand.h"

BindCommand::BindCommand(map<string, string> &pathTable) {
    this->pathTable = pathTable;
}

void BindCommand::doCommand(vector<string> args) {
    string destination = args[0];
    string source = args[1];
    if ((pathTable.count(destination) <= 0)||(pathTable.count(source) <= 0)) {
        throw logic_error("assignment of unrecognized var");
    }
    if (source[0] == '\"') {
        source.erase(source.begin());
        source.erase(source.begin() + (source.size() - 1));
        (pathTable.find(destination)->second) = source;
    } else {
        (pathTable.find(destination)->second) = (pathTable.find(source)->second);
    }
}
