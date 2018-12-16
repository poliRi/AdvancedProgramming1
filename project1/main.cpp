#include <iostream>
#include "Lexer.h"
#include "Parser.h"

int main() {
    Lexer *lex = new Lexer();
    auto tokens = lex->Lex("/Users/polinarabinovich/CLionProjects/project1/project1.txt");
    Parser parser;
    parser.parse(tokens);

    return 0;
}