#Reverse Polish Notation
In mathematical expressions, we use what is regarded as infix notation, where the operator is in between it's operands and is straight-forward for a human to evaluate. Expressions such as 2 + 9 - (4 * 2) are all in infix. Reverse Polish Notation (RPN) or Postfix expressions are an alternative mathematical notation where every operator follows it's operands. This notation has uses in numerous fields of computer science, especially in mathematic expression evaluation.

#Shunting Yard Algorithm
The shunting yard algorithm was developed by Edsger Dijkstra to convert infix notation into RPN. It's name is derived from it's operations' unique resemblance to that of a railroad shunting yard. The algorithm itself is stack based and has applications in countless fields of mathematics and computer science.

#C++ Implementation
I have developed an implementation of this algorithm in C++, which includes 4 classes. The first, is a Token class to compute and store various properties of the tokens involved with the algorithm. Furthermore, I have created a Stack data structure which utilizes dynamic memory allocation to resemble the primitive data structure. The third class is named StringTools, which are a collection of string operations such as splitting a string into an array which are incredibly useful to this instance. Finally, a class has been created called ShuntingYard, which has three primary functions: setExpression(), to store the infix input; formatExpression(), which formats the input to allow it to be tokenized; convertToPostfix(), which is a string function that returns the postfix equivalent of the infix expression. 
To use my library, follow these steps:
<ol>
<li>Import the ShuntingYard.h file, and create an object for it</li>
<li>Set the infix expression using either the constructor or the setExpression() function</li>
<li>Call the void formatExpression() to tokenize the infix input
</li>
<li>Store the return value of convertToPostfix() in a string
</li>
</ol>

