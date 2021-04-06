#include "general_header.h"
#include "outputRPN.h"

void WriteOperation(stack * pHead)
{
	switch (pHead->op)
	{
	case 3:
		printf("+ ");
		break;
	case 4:
		printf("- ");
		break;
	case 5:
		printf("* ");
		break;
	case 6:
		printf("/ ");
		break;
	case 7:
		printf("^ ");
		break;
	case 8:
		printf("sin ");
		break;
	case 9:
		printf("cos ");
		break;
	case 10:
		printf("tan ");
		break;
	case 11:
		printf("ln ");
		break;
	case 12:
		printf("log ");
		break;
	case 13:
		printf("exp ");
		break;
	case 1:
		printf("( ");
		break;
	case 2:
		printf(") ");
		break;
	default:
		printf("NULL");
		break;
	}
}

void WriteRPN(stack * pHead)
{
	if (pHead)
	{
		if (pHead->op == 0)
			printf("%.f ", pHead->value);
		else
			WriteOperation(pHead);
		WriteRPN(pHead->pNext);
	}
}
void FILE_WriteOperation(stack * pHead, FILE * fptr)
{
	switch (pHead->op)
	{
	case 3:
		fprintf(fptr, "+ ");
		break;
	case 4:
		fprintf(fptr, "- ");
		break;
	case 5:
		fprintf(fptr, "* ");
		break;
	case 6:
		fprintf(fptr, "/ ");
		break;
	case 7:
		fprintf(fptr, "^ ");
		break;
	case 8:
		fprintf(fptr, "sin ");
		break;
	case 9:
		fprintf(fptr, "cos ");
		break;
	case 10:
		fprintf(fptr, "tan ");
		break;
	case 11:
		fprintf(fptr, "ln ");
		break;
	case 12:
		fprintf(fptr, "log ");
		break;
	case 13:
		fprintf(fptr, "exp ");
		break;
	case 1:
		fprintf(fptr, "( ");
		break;
	case 2:
		fprintf(fptr, ") ");
		break;
	default:
		fprintf(fptr, "NULL");
		break;
	}
}

void FILE_WriteRPN(stack * pHead, FILE * fptr)
{
	if (pHead)
	{
		if (pHead->op == 0)
			fprintf(fptr, "%.f ", pHead->value);
		else
			FILE_WriteOperation(pHead, fptr);
		FILE_WriteRPN(pHead->pNext, fptr);
	}
}
