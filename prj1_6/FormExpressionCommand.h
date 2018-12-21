#include "interface.h"

class FormExpressionCommand : public Command {

private:
    string infix;
    map<string, double> symbolTable;

public:
    FormExpressionCommand(map<string, double> symbolTable);
    void doCommand(vector<string> args);
    void evaluateVars();
    bool isSignelNumber();
    int precedence(string oper);
    int precedence(char oper);
    bool isNumber(string token);
    bool isOperator(string token);
    bool isDigit(char c);
    void toTokens();
    void rewriteNegativeExp();
    string convertToPostfix();
    Expression* fromPostfixToExpr(string postfix);
};
