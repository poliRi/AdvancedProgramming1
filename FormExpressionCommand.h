#ifndef FORMEXPRESSIONCOMMAND_H
#define FORMEXPRESSIONCOMMAND_H
#include "interface.h"

/*
class FormExpressionCommand is in charge of evaluating the expression it receives.
it does this by a series of actions, including split into the tokens, conversion to
postfix format, and calculating the numerical value of the expression
*/
class FormExpressionCommand : public Command {

    private:
        map<string, double> *symbolTable;
        string infix;
        Expression* e;
        string result;

    public:
        FormExpressionCommand(map<string, double> &symbolTable);
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
        string getResultStr();
        ~FormExpressionCommand();
};

#endif // FORMEXPRESSIONCOMMAND_H

