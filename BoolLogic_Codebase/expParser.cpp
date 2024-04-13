#include <iostream>
using namespace std;

/*
This file is home to the expression parser.
When passed a value from the input parser, this should do the following things:
	Confirm that there is valid input
 	Check for parentheses, make sure they all match and are balanced
  	Check for invalid statements, ex: (T &)
	Perform any conversions necessary to make expression evaluatable by the eval module
 		This could be type conversions, separation of expressions, or anything else to make
   		evaluation easier.
*/
