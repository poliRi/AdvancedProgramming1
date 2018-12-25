#include "BindCommand.h"

/*
BindCommand: constructor
*/
BindCommand::BindCommand(map<string, string> &pathTable) {
    //hold reference to the main paths table of the program
    this->pathTable = &pathTable;
}

/*
binds the given variable value to the path of the given source expression.
the source expression could be whether a path address, or name of other variable
*/
void BindCommand::doCommand(vector<string> args) {
    string destination = args[0];
    string source = args[1];
    //if one of the operands does not exist
    if ((pathTable->count(destination) <= 0)||((source[0] != '\"')&&(pathTable->count(source) <= 0))) {
        throw logic_error("assignment of unrecognized var");
    }
    //if the source expression is a path address
    if (source[0] == '\"') {
        //remove qoutation marks
        source.erase(source.begin());
        source.erase(source.begin() + (source.size() - 1));
        //assign to destination
        (pathTable->find(destination)->second) = source;
        //if the source expression is a var name
    } else {
        //assign the source path to the destination path
        (pathTable->find(destination)->second) = (pathTable->find(source)->second);
    }
}
