#ifndef FORMEXPRESSIONCOMMAND_H
#define FORMEXPRESSIONCOMMAND_H
#include "interface.h"

class FormExpressionCommand : public Command {

    private:
        map<string, double> symbolTable;
        string infix;
        Expression* e;

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
};

#endif // FORMEXPRESSIONCOMMAND_H

