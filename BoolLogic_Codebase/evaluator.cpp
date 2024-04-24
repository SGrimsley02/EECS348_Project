#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <cctype>

using namespace std;
//this has little to no error implementation and only works when the expression is error free
//the expParser or inputParser needs to check the expression for errors before passing it to this class
class BooleanExpressionCalculator {
private:
    unordered_map<char, bool> variables;

    bool evaluateExpression(const string& expression) {
        stack<char> operators;
        stack<bool> operands;

        for (char c : expression) {
            //cout << "Processing character: " << c << endl; // Debug statement
            if (isalpha(c)) { // Variable
                operands.push(variables[c]);
            } else if (c == '(') { // Left parenthesis
                operators.push(c);
            } else if (c == ')') { // Right parenthesis
                while (!operators.empty() && operators.top() != '(') {
                    evaluateOperation(operators.top(), operands);
                    operators.pop();
                }
                if (!operators.empty()) operators.pop(); // Pop '(' if present
            } else if (isOperator(c)) { // Operator
                while (!operators.empty() && (precedence(operators.top()) >= precedence(c))) {
                    evaluateOperation(operators.top(), operands);
                    operators.pop();
                }
                operators.push(c);
            }
        }

        while (!operators.empty()) {
            evaluateOperation(operators.top(), operands);
            operators.pop();
        }

        if (operands.empty()) {
            cout << "Error: No result obtained." << endl;
            return false;
        }

        return operands.top();
    }

    void evaluateOperation(char op, stack<bool>& operands) {
    if (op == '!') {
        bool operand = operands.top(); operands.pop();
        operands.push(!operand);
    } else {
        bool operand2 = operands.top(); operands.pop();
        bool operand1 = operands.top(); operands.pop();
        //cout << "Evaluating operation: " << operand1 << " " << op << " " << operand2 << endl; // Debug statement
        bool result;
        switch (op) {
            case '&': result = operand1 && operand2; break;
            case '|': result = operand1 || operand2; break;
            case '@': result = !(operand1 && operand2); break;
            case '$': result = (operand1 != operand2); break; // XOR operation
        }
        operands.push(result);
    }
}




    int precedence(char op) {
        if (op == '!' || op == '@') return 4;
        else if (op == '&') return 3;
        else if (op == '|') return 2;
        else if (op == '$') return 1;
        else return 0;
    }

    bool isOperator(char c) {
        return c == '&' || c == '|' || c == '!' || c == '@' || c == '$';
    }

public:
    void setVariable(char variable, bool value) {
        variables[variable] = value;
    }

    bool evaluate(const string& expression) {
        cout << "Evaluating expression: " << expression << endl;
        return evaluateExpression(expression);
    }
};
/*
This is where the actual evaluation occurs. It should be able to take an input from exp parser,
then give a boolean output corresponding to the original equation.
    Note: While variable inputs can and should be in the final product, they will take a somewhat
    different approach to implement since the final output will likely not be just True or False.
    As such, start with the simpler case, figure out what's needed for that, then build from there.
The output of this should be able to be passed back to the interface to be shown to the user.
*/
