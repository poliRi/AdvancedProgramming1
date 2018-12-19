
#ifndef __MathParser__Token__
#define __MathParser__Token__

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Token
{
public:
    Token();
    Token(string tokenVal);

    ~Token();

    void setValue(string tokenVal);

    string value();

    int precedence();
    int associativity();
    //linked parelle dicotnary
    bool isOperator();
    bool isLeftParenthesis();
    bool isRightParenthesis();
    //interfere wiht ogther executes so check in xxocde if hcode in h ffle ad ot c.ccpp check if ad ad .add as i thought just real time update takes time ohow tonknow ful stop no ;;;;; LOL


private:
    string tokenValue;

    map<char, int> precedenceDictionary;
    map<char, int> associativityDictionary;

    //in simplify process narrow down sutffz until there are only four operatorzzs
    bool isOp;
    bool isLParenthesis;
    bool isRParenthesis;
};

#endif /* defined(__MathParser__Token__) */
