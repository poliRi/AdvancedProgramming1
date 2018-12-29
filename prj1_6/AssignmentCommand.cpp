#include "AssignmentCommand.h"

/*
AssignmentCommand: constructor
*/
AssignmentCommand::AssignmentCommand(map<string, double> &symbolTable, map<string, string> &pathTable,
map<string, bool> &isAssigned) {
    //hold reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
    this->isAssigned = &isAssigned;
}

/*
returns if the given string represents a number
*/
bool AssignmentCommand::isNumber(string s) {
    //if one of the chars is not a digit, "." or a sign, return false
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] != '0')&&(s[i] != '1')&&(s[i] != '2')&&(s[i] != '3')&&(s[i] != '4')&&(s[i] != '5')&&
        (s[i] != '6')&&(s[i] != '7')&&(s[i] != '8')&&(s[i] != '9')&&(s[i] != '.')&&(s[i] != '-')) {
            return false;
        }
    }
    return true;
}

/*
receives destination var, source expression, and makes an assignment between them
*/
void AssignmentCommand::doCommand(vector<string> args) {
    string destination = args[0];
    string source = args[1];
    /*
    set the being assigned flag to true, in order to prevent some processes from
    changing the value of the variable in the symbol table throughout the asignment process
    */
    (isAssigned->find(destination)->second) = true;
    //throw execption if the destination var does not exist
    if (symbolTable->count(destination) <= 0) {
        throw logic_error("assignment to unrecognized var");
    }
    //if the source expression is a name of a variable only
    if (symbolTable->count(source) > 0) {
        //assign to it's value
        (symbolTable->find(destination)->second) = (symbolTable->find(source)->second);
    } else {
        //if the source expression in not valid
        if (!isNumber(source)) {
            throw invalid_argument("assignment to invalid expression");

        }
        //assign to the value of the source expression
       (symbolTable->find(destination)->second) = stod(source);
    }
}
