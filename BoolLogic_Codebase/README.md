All code for the Boolean Logic Simulator can be found here.

Modules are divided into an expression evaluator, expression parser, input parser, and a user interface. The intended dataflow is as follows:

User --> UI --> Input Parse --> Exp Parse --> Eval --> UI --> User

Any helper functions specific to these functionalities should be found within the same file. Additional files may arise. For instance, it may be worthwhile to separate cases with and without variables, as these will likely need to be handled quite differently.

Code should follow guidelines set by the architecture and requirements documents, in addition to any previously mentioned best practices. Notably, all code should be accompanied with comments, and variable, function, and class names should be descriptive and self documenting in order to aid in both production and maintainability.
