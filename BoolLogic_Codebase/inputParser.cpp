#include <iostream>
using namespace std;

/* 
This file should define an input parser. It should take an input string from the interface, then turn it into something usable by the evaluator.
  This may or may not be a string, it will depend on implementation of expression parser.
  If there are characters not necessary for the expression parser, then these characters should be removed
  by the input parser. Ex: spaces
Throw errors if input is bad, these will be caught by the interface.
Return the output of the evaluator, or return the string to the interface to then be sent to the evaluator
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
            } else if (!isalnum(ch) && ch != ' ') {
                // If a character is not alphanumeric, an operator, or a space, it is considered invalid
                throw runtime_error("Error: Invalid character encountered.");
            }
            // Check for invalid alphanumeric characters that are not 'T' or 'F'
            if (isalnum(ch) && !truthValues.count(ch)) {
                throw runtime_error("Error: Invalid truth value.");
            }
            lastChar = ch; // Update the last character variable for the next iteration
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
