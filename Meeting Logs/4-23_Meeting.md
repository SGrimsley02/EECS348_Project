# Meeting Log
**Date:** Apr 3, 5:00pm

**Purpose:** Software Implementation

**Attendance:** Sam, Blair, Justin, Jason, Conner 

## Summary
This meeting was held without Roop due to a large number of conflicts the rest of the semester. For this same reason, this is likely the last meeting.

We discussed the implementation of the Logic Simulator. What follows are important notes from the meeting:

- Input parser: Send a string to exp parser. Mostly an error handler, but will convert T and F to 1 and 0 respectively. Returns either the result of the expression, or an error code.
- Evaluator/Exp Parser: Likely to be combined due to C++ provided bitwise operators.
- UI: Prompt the user for input, tells them if there's errors, allows the user to end the program when done.

The following lists how the implementation will be broken up by group member:
- Connor, Roop: Evaluator/Exp Parser
- Jason, Justin: Error Handling with Input Parser
- Sam, Blair: UI

Other things of note:
- We will not be completing additional test cases
- More information on Error #4 and the possibility of assignment will be provided soon

## Important Dates
- April 28: All code must be completed and at least mostly tested
- April 29: User Manual work begins
- May 2: ***FINAL DEADLINE***

