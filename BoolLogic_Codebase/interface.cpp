#include <iostream>
#include "evaluator.h"
#include "isValidExpression.h"
using namespace std;

/*
This program will handle any and all interaction with the user. It should be able to ask the user for input
before passing off to the input parser, then it should send the output of the evaluator back to the user
in a readable format.
This should also have a way of handling any errors that may arise, giving the user a message saying what went
wrong without breaking the program.
Lastly, this should have a way to end the program.
The interface will be a simple command line interface, with the user entering a boolean expression to evaluate.
*/

int main() {
    //Introduction
    cout << "Welcome to the Boolean Logic Evaluator!" << endl;
    cout << "Please enter a boolean expression to evaluate." << endl;
    cout << "Enter 'exit' to quit the program." << endl;
    cout << "Operators: & (AND), | (OR), ! (NOT), @ (NAND), $ (XOR), () (Parenthesis)" << endl;
    cout << "Use T for True and F for False." << endl;
    cout << "Example: (T&F)|T" << endl;

    //Get input from user
    string input;
    while (true) {
        cout << "\nEnter a boolean expression: ";
        //grab input until reach newline character 
        char cur = ' ';
        string input = "";
        while (cur != '\n'){
            cur = cin.get();
            if (cur != ' ' && cur != '\n'){
                input += cur;
            }
        }

        //Check to exit
        if (input == "exit" or input == "Exit" or input == "EXIT" or input == "e" or input == "E") {
            cout << "Goodbye!" << endl;
            break;
        }
        //Still need to actually parse the input, as of now just sending it straight to eval module for testing
        //Final workflow will likely be to either send input to exp parse and from there to evaluator,
        //Or send input to exp parse to clean input, then send from here to eval. Just depends on parse implementation
        
        //Check if the input is a valid expression
        if (!isValidExpression(input)) {
            continue; //Skip to the next iteration of the loop, prompting for new input
        }
        
        //Evaluate the expression
        try {
            BooleanExpressionCalculator calc;
            calc.setVariable('T',true);
            calc.setVariable('F',false);
            bool result = calc.evaluate(input);
            //could be rewritten, kinda redundant
            if (isValidExpression(input)){
                cout << "The result of the expression is: " << (result ? "True" : "False") << endl; //convert from 1/0 to T/F
            }
        } catch (const char* e) { //Catch errors from the parser
            cout << "Error: " << e << endl; //Print message may change as we figure out what errors are
        }
    }
    return 0;
}
