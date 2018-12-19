
#include "Token.h"
//i otught have to comptue sine befoer poswtif xos that mus tbe firstreplace funciton wiht it's diefnitno
Token::Token()
{
    isOp = false;
    isLParenthesis = false;
    isRParenthesis = false;

    precedenceDictionary['+'] = 2;
    precedenceDictionary['-'] = 2;
    precedenceDictionary['*'] = 3;
    precedenceDictionary['/'] = 3;
    precedenceDictionary['^'] = 4;
    precedenceDictionary['('] = 1;

    associativityDictionary['+'] = 0;
    associativityDictionary['-'] = 0;
    associativityDictionary['*'] = 0;
    associativityDictionary['/'] = 0;
    associativityDictionary['^'] = 1;
    associativityDictionary['('] = 0;

    //can lal tings summationszzs sassa azzwelle 2x + 1 for rnagzzs else retrn the no; nfuncoitn al stuff + functional stuff wihc is claucetin basebacase
}
//while degrre of seuence > 0 if is 0 reuttn rsequenec if exprison has no funtoins treutn rthe saoltuoj of that experssion
Token::Token(string tokenVal)
{
    tokenValue = tokenVal;

    isOp = false;
    isLParenthesis = false;
    isRParenthesis = false;

    if((((tokenValue[0] == '+' || tokenVal[0] == '-') || tokenVal[0] == '*') || tokenVal[0] == '/') || tokenVal[0] == '^')
    {
        isOp = true;
    }
    else if(tokenValue[0] == '(')
    {
        isLParenthesis = true;
    }
    else if(tokenValue[0] == ')')
    {
        isRParenthesis = true;
    }

    precedenceDictionary['+'] = 2;
    precedenceDictionary['-'] = 2;
    precedenceDictionary['*'] = 3;
    precedenceDictionary['/'] = 3;
    precedenceDictionary['^'] = 4;
    precedenceDictionary['('] = 1;

    associativityDictionary['+'] = 0;
    associativityDictionary['-'] = 0;
    associativityDictionary['*'] = 0;
    associativityDictionary['/'] = 0;
    associativityDictionary['^'] = 1;
    associativityDictionary['('] = 0;
}

Token::~Token()
{
}

void Token::setValue(string tokenVal)
{
    tokenValue = tokenVal;

    if((((tokenValue[0] == '+' || tokenVal[0] == '-') || tokenVal[0] == '*') || tokenVal[0] == '/') || tokenVal[0] == '^')
    {
        isOp = true;
    }
    else if(tokenValue[0] == '(')
    {
        isLParenthesis = true;
    }
    else if(tokenValue[0] == ')')
    {
        isRParenthesis = true;
    }
}

string Token::value()
{
    return tokenValue;
}

int Token::precedence()
{
    return precedenceDictionary[tokenValue[0]];
}

int Token::associativity()
{
    return associativityDictionary[tokenValue[0]];//line o best fit ai splti yb , or tab look for repated vlaues it is delimetsz {{
}

bool Token::isOperator()
{
    return isOp;
}

bool Token::isLeftParenthesis()
{
    return isLParenthesis;
}

bool Token::isRightParenthesis()
{
    return isRParenthesis;
}