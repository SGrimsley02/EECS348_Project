#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cctype>
/*
This is where the actual evaluation occurs. It should be able to take an input from exp parser,
then give a boolean output corresponding to the original equation.
    Note: While variable inputs can and should be in the final product, they will take a somewhat
    different approach to implement since the final output will likely not be just True or False.
    As such, start with the simpler case, figure out what's needed for that, then build from there.
The output of this should be able to be passed back to the interface to be shown to the user.
*/

//Inputs: string with 'T', 'F', '(', ')', '@', '&', '$', '!', ' ', '|'

//Output: boolean of 1 or 0

//Note: The evaluator can work for whatever variables you assign to it with the set variable method.  Also it doesn't check for errors.

using namespace std;

class BooleanExpressionCalculator {
private:
    // Map to store variables and their boolean values
    unordered_map<char, bool> variables;

    // Function to evaluate the boolean expression
    bool evaluateExpression(const string& expression) {
        // Stacks to store operators and operands during evaluation
        stack<char> operators;
        stack<bool> operands;

        // Iterate through each character in the expression
        for (char c : expression) {
            if (isalpha(c)) { // If character is a variable
                operands.push(variables[c]);
            } else if (c == '(') { // If character is a left parenthesis
                operators.push(c);
            } else if (c == ')') { // If character is a right parenthesis
                // Evaluate operators until matching left parenthesis is found
                while (!operators.empty() && operators.top() != '(') {
                    evaluateOperation(operators.top(), operands);
                    operators.pop();
                }
                if (!operators.empty()) operators.pop(); // Pop '(' if present
            } else if (isOperator(c)) { // If character is an operator
                // Evaluate higher precedence operators before current operator
                while (!operators.empty() && (precedence(operators.top()) >= precedence(c))) {
                    evaluateOperation(operators.top(), operands);
                    operators.pop();
                }
                operators.push(c);
            }
        }

        // Evaluate remaining operators
        while (!operators.empty()) {
            evaluateOperation(operators.top(), operands);
            operators.pop();
        }

        // Check if any result obtained
        if (operands.empty()) {
            cout << "Error: No result obtained." << endl;
            return false;
        }

        return operands.top();
    }

    // Function to evaluate individual boolean operations
    void evaluateOperation(char op, stack<bool>& operands) {
        if (op == '!') { // If operator is NOT
            bool operand = operands.top(); operands.pop();
            operands.push(!operand);
        } else { // For other operators (AND, OR, NOR, XOR)
            bool operand2 = operands.top(); operands.pop();
            bool operand1 = operands.top(); operands.pop();
            bool result;
            // Perform the corresponding operation based on the operator
            switch (op) {
                case '&': result = operand1 && operand2; break; // AND
                case '|': result = operand1 || operand2; break; // OR
                case '@': result = !(operand1 && operand2); break; // NOR (NOT AND)
                case '$': result = (operand1 != operand2); break; // XOR
            }
            operands.push(result);
        }
    }

    // Function to determine precedence of operators
    int precedence(char op) {
        if (op == '!' || op == '@') return 4; // Highest precedence for NOT and NOR
        else if (op == '&') return 3; // Higher precedence for AND
        else if (op == '|') return 2; // Lower precedence for OR
        else if (op == '$') return 1; // Lowest precedence for XOR
        else return 0; // Parentheses have lowest precedence
    }

    // Function to check if a character is an operator
    bool isOperator(char c) {
        return c == '&' || c == '|' || c == '!' || c == '@' || c == '$';
    }

public:
    // Function to set variable and its value
    void setVariable(char variable, bool value) {
        variables[variable] = value;
    }

    // Function to evaluate boolean expression
    bool evaluate(const string& expression) {
        return evaluateExpression(expression);
    }
};

int main() {
    // Example usage of BooleanExpressionCalculator
    BooleanExpressionCalculator calculator;
    calculator.setVariable('A', true);
    calculator.setVariable('B', false);
    cout << "Result: " << calculator.evaluate("(!A & B) | (A & !B)") << endl; // Example expression evaluation

    return 0;
}
