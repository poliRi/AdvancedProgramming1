#include "interface.h"

#include "ShuntingYard.h"



int main() {
//    Interpreter interpreter;
//    string path = "/Users/polinarabinovich/CLionProjects/project1/project1.txt";
//    ifstream file;
//    file.open(path);
//    //split string to lines in file by "\n"
//    auto lines = Utils::Split(file, "\n");
//    //read each line and send to interpretation
//    for (auto line : lines) {
//        vector<string> words = interpreter.Lexer(line);
//        interpreter.Parser(words);
//    }
//    file.close();

    ShuntingYard *sh = new ShuntingYard("3 + (4 / 2) * 5");
//sh->setExpression("2 + 9 - (4 * 2)");
    sh->formatExpression();
    string s = sh->convertToPostfix();

    Expression* result2 = sh->fromPostFixToExpr(s);
//    result2->Calculate();
//    cout << result2->Calculate() << endl;

    Expression *e = new Plus(new Number(3), new Mult(new Div(new Number(4), new Number(2)), new Number(5)));
//    cout << e->Calculate() << endl;

    return 0;

}
