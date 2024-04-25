#include <iostream>
#include <string>
#include <stack>
#include <cctype>

bool isValidExpression(const std::string& expression) {
    if (expression.empty()) {
        std::cerr << "Error: Empty expression." << std::endl;
        return false;
    }

    std::stack<char> parenthesesStack;
    bool operandExpected = true;
    char prevChar = '$'; // Initialize prevChar with a special character

    for (char ch : expression) {
        if (ch != 'T' && ch != 'F' && ch != ' ' && ch != '&' && ch != '|' &&
            ch != '!' && ch != '@' && ch != '$') {
            std::cerr << "Error: Unrecognized symbol '" << ch << "'." << std::endl;
            return false;
        }

        if (!operandExpected && (ch == '&' || ch == '|' || ch == '!' || ch == '@' || ch == '$')) {
            std::cerr << "Error: Consecutive operators." << std::endl;
            return false;
        }

        if (operandExpected && ch == '!') {
            std::cerr << "Error: Missing operand after NOT." << std::endl;
            return false;
        }

        if (prevChar == '(' && (ch == '&' || ch == '|' || ch == '!' || ch == '@' || ch == '$')) {
            std::cerr << "Error: Missing operand after '" << prevChar << "'." << std::endl;
            return false;
        }

        if (prevChar == ')' && (ch == 'T' || ch == 'F')) {
            std::cerr << "Error: Missing operator after ')'" << std::endl;
            return false;
        }

        if (ch == '(') {
            parenthesesStack.push(ch);
        } else if (ch == ')') {
            if (parenthesesStack.empty()) {
                std::cerr << "Error: Missing opening parenthesis for ')'" << std::endl;
                return false;
            }
            parenthesesStack.pop();
        }

        operandExpected = (ch == 'T' || ch == 'F' || ch == '(' || ch == '!');
        prevChar = ch;
    }

    if (!parenthesesStack.empty()) {
        std::cerr << "Error: Missing closing parenthesis." << std::endl;
        return false;
    }

    if (prevChar == '&' || prevChar == '|' || prevChar == '!' || prevChar == '@' || prevChar == '$') {
        std::cerr << "Error: Consecutive operators." << std::endl;
        return false;
    }

    return true;
}

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
