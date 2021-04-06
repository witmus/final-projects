#pragma once

//function adds a given number to the computing list
void PushNumber(stack ** ptr, int number);

//function performs the given operation using values from the computing list, then puts the result on this list
void PushPartialResult(stack ** ptr, operation oper);

//main function for calculating values of RPN expressions using the above functions
void CalculateExpressions(stack ** head_ptr, stack ** computing_ptr);