#pragma once

//function adds a given number or operation to the output list
void AddElementToOutput(stack ** head, stack ** tail, int number, operation oper);

//function moves the elements from the stack to the output list according to the given operation's priority, called by the function PushOperation
void ReduceStack(stack ** stack_pointer, operation oper, stack ** out_head_pointer, stack ** out_tail_pointer);

//function adds a given operation to the stack
void PushOperation(stack ** stack_pointer, operation oper, stack ** out_head_pointer, stack ** out_tail_pointer);

//function moves all the remaining elements from the stack to the output list
void ClearStack(stack ** stack_pointer, stack ** out_head_pointer, stack ** out_tail_pointer);

//main function for creating RPN expression using all of the above functions
void CreatePostfixExpression(char * buffer, stack ** out_head_pointer, stack ** out_tail_pointer, stack ** stack_pointer);