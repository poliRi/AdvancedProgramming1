//
//  Queue.h
//  MathParser
//
//  Created by Vedant Mathur on 7/28/15.
//  Copyright (c) 2015 Vedant Mathur. All rights reserved.
//

#ifndef __MathParser__Queue__
#define __MathParser__Queue__

#include "Token.h"
#include <iostream>
#include <string>

using namespace std;

class Queue
{
public:
    Queue();
    ~Queue();

    void push(Token token);

    char* pop();

    size_t size();

private:
    char** queueArray;

    int queueIndex;
};

#endif /* defined(__MathParser__Queue__) */
