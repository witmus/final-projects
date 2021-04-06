#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum operation { null, open_bracket, close_bracket, add, sub, mtp, divide, power, sine, cosine, tang, ln, decimal_log, expon } operation;

typedef struct stack stack;

struct stack
{
	double value;
	operation op;
	stack * pNext;
	stack * pPrev;
};

//function reads a text file into a dynamic array of chars
char * ReadFile(FILE * file);

//function divides buffer into seperate expressions
char ** CreateExpressionsArray(char * buffer, int lines);

//auxiliary function for counting expressions from the source file
int CountLines(char * buffer);

//function deletes dynamically allocated list
void DeleteList(stack * pHead);