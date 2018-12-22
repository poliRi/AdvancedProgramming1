#include "ConditionParser.h"

ConditionParser::ConditionParser(vector<string> tokens, map<string, double> symbolTable) {
    this->symbolTable = symbolTable;
    this->evaluate = new FormExpressionCommand(symbolTable);
    leftExp = "";
    rightExp = "";
    for (auto& token : tokens) {
        if (token.front() == '(') {
            token.erase(token.begin());
        }
        if (token.back() == ')') {
          token.erase(token.begin() + (token.size() - 1));
        }
    }
    int i;
    for (i = 0; i < tokens.size() - 1; i++) {
        if ((tokens[i] == "<")||(tokens[i] == ">")||(tokens[i] == "<=")||
        (tokens[i] == ">=")||(tokens[i] == "==")||(tokens[i] == "!=")) {
            oper = tokens[i];
            i++;
            break;
        }
        leftExp += tokens[i];
    }
    while (i < tokens.size() - 1) {
        rightExp += tokens[i];
        i++;
    }
}

bool ConditionParser::isTrue() {
    double leftOperand;
    double rightOperand;
    vector<string> params = {};
    params.push_back(leftExp);
    evaluate->doCommand(params);
    leftOperand = stod(evaluate->getResultStr());
    params.clear();
    params.push_back(rightExp);
    evaluate->doCommand(params);
    rightOperand = stod(evaluate->getResultStr());
    if (oper == "<") {
        return (leftOperand < rightOperand);
    } else if (oper == ">") {
        return (leftOperand > rightOperand);
    } else if (oper == "<=") {
        return (leftOperand <= rightOperand);
    } else if (oper == ">=") {
        return (leftOperand >= rightOperand);
    } else if (oper == "==") {
        return (leftOperand == rightOperand);
    } else if (oper == "!=") {
        return (leftOperand != rightOperand);
    }
}
