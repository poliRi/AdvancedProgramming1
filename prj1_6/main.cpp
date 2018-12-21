#include "interface.h"
#include "Interpreter.h"
#include "Utils.h"
#include "FormExpressionCommand.h"

int main(int argc, char *argv[]) {
    /*Interpreter* interpreter = new Interpreter();
    if (argc == 2) {
        string fileName = argv[1];
        vector<string> words;
        ifstream file;
        file.open(fileName);
        if (file.is_open()) {
            auto lines = Utils::Split(file, "\n");
            for (auto& line : lines) {
                vector<string> words = interpreter->Lexer(line);
                interpreter->Parser(words);
            }
            file.close();
        } else {
            cerr << "error opening file" << endl;
        }
    } else if (argc == 1) {
        string line;
        while (line != "") {
            getline (cin,line);
            vector<string> words = interpreter->Lexer(line);
            interpreter->Parser(words);
        }
    } else {
        cout << "invalid number of arguments" << endl;
    }*/


    /*Interpreter* interpreter = new Interpreter();
    string fileName = "/Users/polinarabinovich/CLionProjects/project1/project1.txt";
    vector<string> words = interpreter->Lexer(fileName);
    interpreter->Parser(words);*/

    vector<string> v = {};
    map<string, double> m = {{"heading", 15} , {"throttle", 7.8}};
    Command* c = new FormExpressionCommand(m);
    v.push_back("(- heading / 70)*(throttle/12)");
    c->doCommand(v);

    return 0;
}
