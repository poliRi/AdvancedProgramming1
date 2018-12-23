#include "interface.h"
#include "Interpreter.h"
#include "Utils.h"
#include "FormExpressionCommand.h"

int main(int argc, char *argv[]) {
    /*if (argc == 2) {
        string fileName = argv[1];
        vector<string> words;
        ifstream file;
        file.open(fileName);
        if (file.is_open()) {
            auto lines = Utils::Split(file, "\n");
            map<string, double> symbolTable = {};
            map<string, string> pathTable = {};
            Interpreter* interpreter = new Interpreter(lines, symbolTable, pathTable);
            int currentLine;
            for (currentLine = 0; currentLine < lines.size() - 1; currentLine++) {
                vector<string> words = interpreter->Lexer(currentLine);
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

    vector<string> v = {};
    map<string, double> m = {{"heading", 15} , {"throttle", 7.8}};
    Command* c = new FormExpressionCommand(m);
    v.push_back("(- heading / 70)*(throttle/12)");
    c->doCommand(v);

    return 0;
}
