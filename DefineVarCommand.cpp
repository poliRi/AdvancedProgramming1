#include "DefineVarCommand.h"

/*
DefineVarCommand: constructor
*/
DefineVarCommand::DefineVarCommand(map<string, double> &symbolTable, map<string, string> &pathTable) {
    //hold a reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
}

/*
in charge of defining a new variable in the program
*/
void DefineVarCommand::doCommand(vector<string> args) {
    string name = args[0];
    //throw exception if the variable's name starts with a digit
    if (isDigit(name[0])) {
        throw invalid_argument("illegal name of var");
    }
    //throw exception if the variable's name does not start with a letter or an underscore
    if ((!isLetter(name[0]))&&(name[0] != '_')) {
        throw invalid_argument("illegal name of var");
    }
    //throw exception if the variable's name contains invalid characters
    for (int i = 1; i < name.size(); i++) {
        if ((!isDigit(name[0]))&&(!isLetter(name[0]))&&(name[0] != '_')) {
            throw invalid_argument("illegal name of var");
        }
    }
    //throw exception if the variable's name is a saved word
    if ((name == "openDataServer")||(name == "connect")||(name == "var")||(name == "while")||
    (name == "if")||(name == "print")||(name == "sleep")) {
        throw invalid_argument("illegal name of var");
    }
    //throw exception if the variable is declared twice
    if (symbolTable->count(name) > 0) {
        throw logic_error("redefinition of var");
    } else {
        //insert initialized values to the tables
        symbolTable->insert(pair<string,double>(args[0],0));
        pathTable->insert(pair<string,string>(args[0]," "));
    }
}

/*
returns if the given char is a digit
*/
bool DefineVarCommand::isDigit(char c) {
    return ((c == '0')||(c == '1')||(c == '2')||(c == '3')||(c == '4')||(c == '5')||(c == '6')||
    (c == '7')||(c == '8')||(c == '9'));
}

bool DefineVarCommand::isLetter(char c) {
    if ((c >= 65)&&(c <= 90)) {
        return true;
    }
    if ((c >= 97)&&(c <= 122)) {
        return true;
    }
    return false;
}
