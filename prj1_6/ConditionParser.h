#ifndef CONDITIONPARSER_H
#define CONDITIONPARSER_H
#include "interface.h"
#include "FormExpressionCommand.h"

/*
class ConditionParser is in charge of parsing and holding a boolean condition,
and return whether is true or false
*/
class ConditionParser {

    private:
        map<string, double> *symbolTable;
        string leftExp;
        string oper;
        string rightExp;
        FormExpressionCommand* evaluate;

    public:
        ConditionParser(vector<string> tokens, map<string, double> &symbolTable);
        bool isTrue();
};

#endif // CONDITIONPARSER_H

