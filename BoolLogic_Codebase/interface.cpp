#include <iostream>
#include "evaluator.h"
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
    cout << "Example: (T&F)|T" << endl << endl;

    //Get input from user
    string input;
    while (true) {
        cout << "Enter a boolean expression: ";
        cin >> input;
        //Check to exit
        if (input == "exit" or input == "Exit" or input == "EXIT" or input == "e" or input == "E") {
            cout << "Goodbye!" << endl;
            break;
        }
        //Evaluate the expression
        try {
            BooleanExpressionCalculator calc;
            cout << "The result of the expression is: " << calc.evaluate(input) << endl; //May need to convert from 1/0 to T/F
        } catch (const char* e) { //Catch errors from the parser
            cout << "Error: " << e << endl; //Print message may change as we figure out what errors are
        }
    }
    return 0;
}