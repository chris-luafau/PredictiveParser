Given the following CFG, create a Predictive Parsing table and write a program to trace input strings. Show the content of the stack after each match.

CFG:

S --> a=E

E --> E+T

E --> E-T

E --> T

T --> T*F

T --> T/F

T --> F

F --> (E)

F --> a

F --> b
