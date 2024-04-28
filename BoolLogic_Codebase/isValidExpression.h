#include <iostream>
#include <string>
#include <stack>
#include <cctype>


bool isValidExpression(const std::string& expression) {
    if (expression.empty()) {
        std::cerr << "Error: No operands or operators present.\n";
        return false;
    }

    std::stack<char> parentheses;
    char prevChar = 0;  //Initialize prevChar with a non-operator to manage initial state

    for (char ch : expression) {
        if (isspace(ch)) continue; // Ignore spaces directly

        //Handle invalid characters
        if (ch != 'T' && ch != 'F' && ch != '!' && ch != '&' && ch != '|' && ch != '@' && ch != '$' && ch != '(' && ch != ')') {
            std::cerr << "Error: Unrecognized operator symbol.\n";
            return false;
        }

        //Handle consecutive operators (not including '!')
        if ((prevChar == '&' || prevChar == '|' || prevChar == '@' || prevChar == '$') && 
            (ch == '&' || ch == '|' || ch == '@' || ch == '$')) {
            std::cerr << "Error: Two consecutive operators.\n";
            return false;
        }

        //Ensure proper operand after NOT
        if (prevChar == '!' && (ch != 'T' && ch != 'F' && ch != '(' && ch != '!')) {
            std::cerr << "Error: Missing operand after NOT.\n";
            return false;
        }

        //Handle operands following each other without an operator
        if ((ch == 'T' || ch == 'F') && (prevChar == 'T' || prevChar == 'F')) {
            std::cerr << "Error: Missing operator between operands.\n";
            return false;
        }

        //Handle invalid character before operator
        if ((prevChar == 0 || prevChar == '(') && (ch == '|' || ch == '&' || ch == '@' || ch == '$')){
            std::cerr << "Error: missing operand before operator.\n";
            return false;
        }

        //Handle invalid character after operator
        if ((prevChar == '|' || prevChar == '&' || prevChar == '@' || prevChar == '$') && (ch == ')')){
            std::cerr << "Error: missing operand after operator.\n";
            return false;
        }

        //Parentheses handling
        if (ch == '(') {
            parentheses.push(ch);
        } else if (ch == ')') {
            if (parentheses.empty()) {
                std::cerr << "Error: Missing opening parenthesis.\n";
                return false;
            }
            parentheses.pop();
        }

        prevChar = ch; //Update last character seen
    }

    //Ensure all opened parentheses have been closed
    if (!parentheses.empty()) {
        std::cerr << "Error: Missing closing parenthesis.\n";
        return false;
    }


    //Ensure the expression does not end with an operator
    if (prevChar == '&' || prevChar == '|' || prevChar == '@' || prevChar == '$' || prevChar == '!') {
        std::cerr << "Error: Expression ends with an operator.\n";
        return false;
    }

    return true;
}

/*list of possible errors
invalid characters, consecutive operators, correct operand after !,
consecutive operands, invalid character before/after operator,
missing parenthesis, ends in operantor. 
*/