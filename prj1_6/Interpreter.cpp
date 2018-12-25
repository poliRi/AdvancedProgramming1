#include "Interpreter.h"
#include "Utils.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "FormExpressionCommand.h"
#include "AssignmentCommand.h"
#include "ConditionParser.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "BindCommand.h"
#include "EnterCharacterCommand.h"

/*
Interpreter: constructor. initializes the set of lines its has to read, and all types of commands
*/
Interpreter::Interpreter(vector<string> lines, map<string, double> &symbolTable, map<string, string> &pathTable) {
    //hold reference to the lines of the current scope
    this->lines = lines;
    //hold reference to the main symbol tables of the program
    this->symbolTable = &symbolTable;
    this->pathTable = &pathTable;
    //initialize the index of the current line to be read
    this->currentLine = 0;
    this->commands = {};
    //initialize all commands
    commands.insert(pair<string,Command*>("openDataServer",(new OpenServerCommand(symbolTable,pathTable))));
    commands.insert(pair<string,Command*>("connect",(new ConnectCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("print",(new PrintCommand(symbolTable))));
    commands.insert(pair<string,Command*>("var",(new DefineVarCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("sleep",(new SleepCommand())));
    commands.insert(pair<string,Command*>("assignment",(new AssignmentCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("bind",(new BindCommand(pathTable))));
    commands.insert(pair<string,Command*>("formExpression",(new FormExpressionCommand(symbolTable))));
    commands.insert(pair<string,Command*>("while",(new WhileCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("if",(new IfCommand(symbolTable, pathTable))));
    commands.insert(pair<string,Command*>("enterc",(new EnterCharacterCommand())));
}

/*
splits the given line to tokens, and returns the result
*/
vector<string> Interpreter::Lexer(int line) {
    vector<string> words = Utils::Split(lines[line], " ");
    return words;
}

/*
in charge of receiving the tokens of the current line, parsing and executing, using the appropriate commands
*/
void Interpreter::Parser(vector<string> words) {
    //this vector will be passed to the right command with additional elements each case
    vector<string> params = {};
    //if the first word in the line is "openDataServer" or "connect" or "print" or "sleep"
    if ((words[0] == "openDataServer")||(words[0] == "connect")||(words[0] == "print")||(words[0] == "sleep")) {
        //pop the right command out of the commands map
        Command* c = commands.find(words[0])->second;
        //pass the rest of the line except for the first word, to the right command
        params = words;
        params.erase(params.begin());
        c->doCommand(params);
    //if the first word in the line is enterc
    } else if ((words[0] == "enterc")||(words[0] == "Enterc")) {
        //pop the right command out of the commands map
        Command* c = commands.find("enterc")->second;
        c->doCommand(params);
       //if the first word in the line defines a variable
    } else if (words[0] == "var") {
        //pop the right command
        Command* c = commands.find(words[0])->second;
        //push the var name to the parameters vector, and execture
        params.push_back(words[1]);
        c->doCommand(params);
        //if in the same line, the new variable was also assigned to a given value
        if (words.size() > 2) {
            params.clear();
            //if it is a bind command, push the destination and the source to be the parameters
            if (words[3] == "bind") {
                Command* bnd = commands.find("bind")->second;
                params.push_back(words[1]);
                params.push_back(words[4]);
                //execute
                bnd->doCommand(params);
               //if it is an assignment command
            } else {
                //construct the source expression
                string expressionsStr = "";
                for (int i = 3; i < words.size(); i++) {
                    expressionsStr += words[i];
                }
                //send to evaluation
                FormExpressionCommand* evaluate = (FormExpressionCommand*)commands.find("formExpression")->second;
                params.push_back(expressionsStr);
                evaluate->doCommand(params);
                params.clear();
                //send the result string to the assignment command as the source expression
                Command* ass = commands.find("assignment")->second;
                params.push_back(words[1]);
                params.push_back(evaluate->getResultStr());
                ass->doCommand(params);
            }
        }
        //if the first word in the line is "while" or "if"
    } else if ((words[0] == "while")||(words[0] == "if")) {
         //tells us if scope parenthesis were given
         bool isScopeParenthesis = ((words.back() == "{")||(lines[currentLine + 1].front() == '{'));
         //put the condition tokens in a vector
         vector<string> conditionTokens = {};
         for (int i = 1; ((i < words.size())&&(words[i] != "{")); i++) {
            conditionTokens.push_back(words[i]);
         }
         //go to the first line in the new scope
         currentLine++;
         if ((isScopeParenthesis)&&(words.back() != "{")) {
            currentLine++;
         }
         //create the condition
         ConditionParser* condition = new ConditionParser(conditionTokens, *symbolTable);
         //if there are scope parenthesis
         if (isScopeParenthesis) {
             //add all the lines in the scope to the parameters vector
             while (lines[currentLine].front() != '}') {
                if (lines[currentLine].front() == '\t') {
                    lines[currentLine].erase(lines[currentLine].begin());
                }
                params.push_back(lines[currentLine]);
                //if the character "}" is not on a separate line
                if ((lines[currentLine].size() > 1)&&(lines[currentLine].back() == '}')) {
                    lines[currentLine].erase(lines[currentLine].begin() + (lines[currentLine].size() - 1));
                    break;
                }
                currentLine++;
             }
            //else, do the same
         } else {
            //add all the lines in the scope to the parameters vector
             while (lines[currentLine].front() == '\t') {
                lines[currentLine].erase(lines[currentLine].begin());
                params.push_back(lines[currentLine]);
                currentLine++;
             }
             //turn back when reaching the index of the first line that is not indented
             currentLine--;
         }
         //call the right type of command
         if (words[0] == "while") {
             WhileCommand* whileCmd = (WhileCommand*)commands.find("while")->second;
             whileCmd->setCondition(condition);
             whileCmd->doCommand(params);
         } else if (words[0] == "if") {
            IfCommand* ifCmd = (IfCommand*)commands.find("if")->second;
            ifCmd->setCondition(condition);
            ifCmd->doCommand(params);
         }
         //if no type of command was recognized and the first word in the line is a name of a variable
    } else if (symbolTable->count(words[0]) > 0) {
        //if it is a bind command, push the destination and the source to be the parameters
        if (words[2] == "bind") {
                Command* bnd = commands.find("bind")->second;
                params.push_back(words[0]);
                params.push_back(words[3]);
                //execute
                bnd->doCommand(params);
                //if it is an assignment command
            } else {
                //construct the source expression
                string expressionsStr = "";
                for (int i = 2; i < words.size(); i++) {
                    expressionsStr += words[i];
                }
                //send to evaluation
                FormExpressionCommand* evaluate = (FormExpressionCommand*)commands.find("formExpression")->second;
                params.push_back(expressionsStr);
                evaluate->doCommand(params);
                params.clear();
                //send the result string to the assignment command as the source expression
                Command* ass = commands.find("assignment")->second;
                params.push_back(words[0]);
                params.push_back(evaluate->getResultStr());
                ass->doCommand(params);
            }
        //if the line is empty or an exit instruction was given, skip to the next line
    } else if (words[0].size() == 0) {
       //if an an exit instruction was given
    } else if (words[0] == "exit") {
        exit(0);
      //throw exception in case of unrecognized operation
    }else {
         throw logic_error("unrecognized operation");
    }
    //promote the index of the current line
    currentLine++;
}

/*
returns the index of the current line being interpreted
*/
int Interpreter::getCurrentLine() {
    return this->currentLine;
}

/*
sets the index of the current line to be interpreted
*/
void Interpreter::setCurrentLine(int line) {
    this->currentLine = line;
}

/*
sets the vector of lines to read, to a single line, in case of user input
*/
void Interpreter::setSingleLineToRead(string line) {
    this->lines.clear();
    this->lines.push_back(line);
}

/*
class Interpreter: constructor
*/
Interpreter::~Interpreter() {
    map<string, Command*>::iterator iter;
    //delete all the commands
    for (iter = commands.begin(); iter != commands.end(); ++iter) {
        delete iter->second;
    }
}
