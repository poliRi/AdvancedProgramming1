#include "interface.h"
#include "Interpreter.h"
#include "Utils.h"

int main() {
    Interpreter interpreter;
    string path = "/Users/polinarabinovich/CLionProjects/project1/project1.txt";
    ifstream file;
    file.open(path);
    //split string to lines in file by "\n"
    auto lines = Utils::Split(file, "\n");
    //read each line and send to interpretation
    for (auto line : lines) {
        vector<string> words = interpreter.Lexer(line);
        interpreter.Parser(words);
    }
    file.close();
    Interpreter *inter = new Interpreter;
    auto tokens = inter->Lexer("/Users/polinarabinovich/CLionProjects/project1/project1.txt");
    //Parser parser;
    //parser.Parser(tokens);

    return 0;
}
