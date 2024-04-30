/*
IMPORTANT NOTE:
This code is not currently being used in the final simulator implementation, as
there were some difficulties with combining this with the rest of the simulator
and some of the checks were less efficient than those that were defined in the
isValidExpression.h file. However, this code ended up being very beneficial in
the debugging of several issues in said file, thus substantially reducing the
time spent fixing those issues. As such, this code is kept here as a reference
and in order to further document the work of the team, even though it is not
explicitly in the final product.
*/


#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cctype> //isalnum function
#include <algorithm> //remove_if function

using namespace std;

class InputParser {
public:
    // The parse method takes a string input, validates it, and transforms 'T' to '1' and 'F' to '0'
    // It throws an exception if the input string contains invalid characters or if the parentheses are unbalanced
    string parse(const string& input) {
        string output; // String to store the transformed and validated expression
        stack<char> parentheses; // Stack to check the balance of parentheses

        unordered_map<char, char> validOperators {
            {'&', '&'}, // AND
            {'|', '|'}, // OR
            {'!', '!'}, // NOT
            {'@', '@'}, // NAND
            {'$', '$'}  // XOR
        };

        std::unordered_map<char, std::string> operatorNames {
            {'&', "AND"},
            {'|', "OR"},
            {'!', "NOT"},
            {'@', "NAND"},
            {'$', "XOR"} 
        };

        // Convert 'T' to '1' and 'F' to '0' for standard boolean values
        unordered_map<char, char> truthValues { {'T', '1'}, {'F', '0'} };
        
        char lastChar = 0; // keep track of the last processed character
        
        for (char ch : input) {
            // Replace 'T' with '1' and 'F' with '0'
            if (truthValues.count(ch)) {
                output.push_back(truthValues[ch]);
            } else if (validOperators.count(ch)) {
                if (validOperators.count(lastChar)) {
                    throw runtime_error("Error: Consecutive operators.");
                }
                // Checks for missing operand if last character isn't alphanumberic, ')', or ' '
                if (!isalnum(lastChar) && lastChar != ')' && lastChar != ' ') {
                    throw runtime_error("Error: Missing operant after " + operatorNames[ch]);
                }
                output.push_back(ch);
            } else if (ch == '(') {
                // Push the opening parenthesis onto the stack and add to the output
                parentheses.push(ch);
                output.push_back(ch);
            } else if (ch == ')') {
                // Match each closing parenthesis with an opening one and add to the output
                if (!parentheses.empty() && parentheses.top() == '(') {
                    parentheses.pop();
                    output.push_back(ch);
                } else {
                    throw runtime_error("Error: Unmatched closing parenthesis.");
                }
            } else if (ch != ' ') {
                if (!isalnum(ch)) {
                    // If a symbol is not an operator, raise error
                    throw runtime_error("Error: Unrecognized operator symbol");
                } else if (islower(ch)) {
                    // If a character is lowercase, alphanumeric and not 'T' or 'F', it is invalid
                    throw runtime_error("Error: Using invalid variable instead of 'T' or 'F'");
                }
            }
            // Check for invalid alphanumeric characters that are not 'T' or 'F'
            if (isalnum(ch) && !truthValues.count(ch)) {
                throw runtime_error("Error: Invalid truth value.");
            }
            lastChar = ch; // Update the last character variable for the next iteration
        }
        // Raise Error if input is empty
        if (output.empty()) {
            throw runtime_error("Error: Empty Expression");
        }
        // Check if last character is an operator and is after an operand
        if (validOperators.count(lastChar) && !validOperators.count(output[0])) {
            throw runtime_error("Error: " + operatorNames[lastChar] + " applied after value, not before");
        }

        // After processing all characters, ensure all opening parentheses have been matched
        if (!parentheses.empty()) {
            throw runtime_error("Error: Unmatched opening parenthesis.");
        }

        // Remove whitespace characters from the output to ensure a clean expression string
        output.erase(remove_if(output.begin(), output.end(), ::isspace), output.end());
        
        return output;
    }
};
