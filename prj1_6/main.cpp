#include "interface.h"
#include "Interpreter.h"
#include "Utils.h"

/*
the main function is in charge of interpreting and executing a given content,
whether given by a single line input from the user, or by a file of code lines
*/
int main(int argc, char *argv[]) {
    /*
    declare the main symbol tables of the program.
    they will be holded in various commands for various purposes during the program
    */
    //maps the variable name to its value
    map<string, double> symbolTable = {};
    //maps the variable name to its address in the simulator
    map<string, string> pathTable = {};
    /*
    maps the variable name to its availability for going through an assignment process at the current moment.
    when being assigned to a new value, its value on the map will be true until the end of the assignment
    process, in order to prevent certain processes in the background from interfering with the assignment
    and changing its desired value
    */
    map<string, bool> isAssigned = {};
    //if a file of code lines was given by the command line
    if (argc == 2) {
        string fileName = argv[1];
        ifstream file;
        file.open(fileName);
        //if the file was opened successfully
        if (file.is_open()) {
            //split the lines in the file into vector of strings
            auto lines = Utils::Split(file, "\n");
            //interpreter declaration. hold the vector of lines it has to read, and the symbol tables
            Interpreter* interpreter = new Interpreter(lines, symbolTable, pathTable, isAssigned);
            //for each current line index given by the interpreter
            while (interpreter->getCurrentLine() < lines.size()) {
                //breaks the line components into vector of tokens
                vector<string> words = interpreter->Lexer(interpreter->getCurrentLine());
                //parse, and execute line
                interpreter->Parser(words);
            }
            file.close();
            //if the file was not successfully opened
        } else {
            cerr << "error opening file" << endl;
        }
        //if no command line arguments was given
    } else if (argc == 1) {
        //declare on interpreter with initialized empty vector of lines to read
        vector<string> lines = {};
        Interpreter* interpreter = new Interpreter(lines, symbolTable, pathTable, isAssigned);
        string line = "";
        //as long as no order has been given to leave the program
        while (true) {
            //get input from the user
            getline (cin,line);
            //set the vector of lines that the interpreter has to read, to the sinlge line of the user input
            interpreter->setSingleLineToRead(line);
            //lex and parse
            vector<string> words = interpreter->Lexer(interpreter->getCurrentLine());
            interpreter->Parser(words);
            /*
            set the current line index back to 0, since the interpreter reads the current
            line within a single element vector of lines each iteration
            */
            interpreter->setCurrentLine(0);
        }
        //if te number of arguments given to the program is invalid
    } else {
        cout << "invalid number of arguments to the program" << endl;
    }
    return 0;
}
