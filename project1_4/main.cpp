#include "interface.h"
#include "Interpreter.h"

int main() {
    Interpreter* interpreter = new Interpreter();
    string fileName = "/Users/polinarabinovich/CLionProjects/project1/project1.txt";
    vector<string> words = interpreter->Lexer(fileName);
    interpreter->Parser(words);

    return 0;
}
