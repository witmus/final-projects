#include "general_header.h"
#include "computing.h"

#define PI 3.141597

void PushNumber(stack ** ptr, int number)
{
	if (*ptr == NULL)
	{
		*ptr = (stack*)malloc(sizeof(stack));
		(*ptr)->value = number;
		(*ptr)->pNext = NULL;
		(*ptr)->pPrev = NULL;
	}
	else
	{
		stack * temp = *ptr;
		*ptr = (stack*)malloc(sizeof(stack));
		(*ptr)->value = number;
		(*ptr)->pNext = temp;
		temp->pPrev = *ptr;
	}
}

void PushPartialResult(stack ** ptr, operation oper)
{
	double result = 0;
	switch (oper)
	{
	case 3:
		result = ((*ptr)->pNext->value) + ((*ptr)->value);
		break;
	case 4:
		result = ((*ptr)->pNext->value) - ((*ptr)->value);
		break;
	case 5:
		result = ((*ptr)->pNext->value) * ((*ptr)->value);
		break;
	case 6:
		result = ((*ptr)->pNext->value) / ((*ptr)->value);
		break;
	case 7:
		result = pow((*ptr)->pNext->value, (*ptr)->value);
		break;
	case 8:
		result = sin(((*ptr)->value)*(PI/180));
		break;
	case 9:
		result = cos(((*ptr)->value)*(PI/180));
		break;
	case 10:
		result = tan(((*ptr)->value)*(PI/180));
		break;
	case 11:
		result = log((*ptr)->value);
		break;
	case 12:
		result = log10((*ptr)->value);
		break;
	case 13:
		result = exp((*ptr)->value);
		break;
	}
	if (oper > 7)
	{
		(*ptr)->value = result;
	}
	else
	{
		stack * temp = *ptr;
		*ptr = (*ptr)->pNext;
		(*ptr)->value = result;
		free(temp);
	}
}

void CalculateExpressions(stack ** head_ptr, stack ** computing_ptr)
{
	stack * temp = *head_ptr;
	while (*head_ptr != NULL)
	{
		if ((*head_ptr)->op == 0)
		{
			PushNumber(computing_ptr, (*head_ptr)->value);
		}
		else
		{
			PushPartialResult(computing_ptr, (*head_ptr)->op);
		}
		*head_ptr = (*head_ptr)->pNext;
	}
	*head_ptr = temp;
}