//
//  Queue.cpp
//  MathParser
//
//  Created by Vedant Mathur on 7/28/15.
//  Copyright (c) 2015 Vedant Mathur. All rights reserved.
//

#include "Queue.h"

Queue::Queue()
{
    queueArray = (char **)malloc(sizeof(char*));

    queueIndex = 0;
}

Queue::~Queue()
{

}

void Queue::push(Token token)
{
    char* chrToken = new char[token.value().size() + 1];
    strcpy(chrToken, token.value().c_str());

    queueArray[queueIndex] = (char *)chrToken;
   // cout << "fry " << chrToken << " w/o " << queueIndex << endl;
    queueIndex++;

    queueArray = (char **)realloc(queueArray, sizeof(char *) * (queueIndex + 1));
}
//problems that can be sovled by code bekaiopinzz cut out linz morse code parternszs
char* Queue::pop()
{
    char** tempArray = (char **)realloc(queueArray, sizeof(*queueArray) * (queueIndex - 1));

    char* temp = queueArray[0];

    //linked list seprate file just not dipfff class pointer aithemczzzzzzz
    //songs that irect i = emind input sych
    for(int i = 1; i < queueIndex; i++)
    {
        tempArray[i - 1] = queueArray[i];
    }

    queueArray = tempArray;
    //cout << "moo " << queueArray[0] << endl;

    --queueIndex;

    return temp;
}

size_t Queue::size()
{
  //  cout << "quo " << queueIndex << endl;
    return queueIndex;
}