#include "general_header.h"
#include "input_analysis.h"

int ReadInt(int * spot, char * buffer)
{
	int length = 0;
	char * number = (char*)malloc(sizeof(char));
	while ((buffer[*spot] > 47) && (buffer[*spot] < 58))
	{
		length++;
		number = realloc(number, length * sizeof(char));
		number[length - 1] = buffer[*spot];
		(*spot)++;
	}
	(*spot) -= 1;
	int result = atoi(number);
	free(number);
	return result;
}

operation ReadOperation(int * spot, char * buffer)
{
	operation oper = 11;
	switch (buffer[*spot])
	{
	case 40:
		oper = 1;
		break;
	case 41:
		oper = 2;
		break;
	case 43:
		oper = 3;
		break;
	case 45:
		oper = 4;
		break;
	case 42:
		oper = 5;
		break;
	case 47:
		oper = 6;
		break;
	case 94:
		oper = 7;
		break;
	case 115:
		oper = 8;
		(*spot) += 2;
		break;
	case 99:
		oper = 9;
		(*spot) += 2;
		break;
	case 116:
		oper = 10;
		(*spot) += 2;
		break;
	case 108:
		(*spot) += 1;
		if (buffer[*spot] == 110)
		{
			oper = 11;
		}
		else
		{
			(*spot) += 1;
			oper = 12;
		}
		break;
	case 101:
		oper = 13;
		(*spot) += 2;
		break;
	}
	return oper;
}