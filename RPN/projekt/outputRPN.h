#pragma once

//function writes an operation as a string
void WriteOperation(stack * pHead);

//function outputs the RPN expression
void WriteRPN(stack * pHead);

//function writes an operation as a string in a text file
void FILE_WriteOperation(stack * pHead, FILE * fptr);

//function outputs the RPN expression in a text file
void FILE_WriteRPN(stack * pHead, FILE * fptr);