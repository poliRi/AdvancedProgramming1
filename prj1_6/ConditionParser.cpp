#include "ConditionParser.h"

/*
ConditionParser: constructor. receives a vector of the condition
component and parses them in order to form a valid condition.
*/
ConditionParser::ConditionParser(vector<string> tokens, map<string, double> &symbolTable) {
    //hold a reference to the main symbol table of the program
    this->symbolTable = &symbolTable;
    //evaluate class member is in charge of calculate the given operands of the given condition
    this->evaluate = new FormExpressionCommand(symbolTable);
    leftExp = "";
    rightExp = "";
    //remove parenthesis from the condition in order to hold valid expression types
    for (auto& token : tokens) {
        if (token.front() == '(') {
            token.erase(token.begin());
        }
        if (token.back() == ')') {
          token.erase(token.begin() + (token.size() - 1));
        }
    }
    //construct the operands of the condition by the given arguments
    int i;
    //start with the left expression
    for (i = 0; i < tokens.size(); i++) {
        if ((tokens[i] == "<")||(tokens[i] == ">")||(tokens[i] == "<=")||
        (tokens[i] == ">=")||(tokens[i] == "==")||(tokens[i] == "!=")) {
            //parse the boolean operator when reaching it
            oper = tokens[i];
            i++;
            //stop parsing th left expression when reaching the operator
            break;
        }
        leftExp += tokens[i];
    }
    //parse the right expression
    while (i < tokens.size()) {
        rightExp += tokens[i];
        i++;
    }
}

/*
returns if the given condition is true
*/
bool ConditionParser::isTrue() {
    double leftOperand;
    double rightOperand;
    //evaluate the left expression
    vector<string> params = {};
    params.push_back(leftExp);
    evaluate->doCommand(params);
    leftOperand = stod(evaluate->getResultStr());
    params.clear();
    //evaluate the right expression
    params.push_back(rightExp);
    evaluate->doCommand(params);
    rightOperand = stod(evaluate->getResultStr());
    //return result according to the right boolean operator
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
