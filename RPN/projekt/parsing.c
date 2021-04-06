#include "general_header.h"
#include "parsing.h"

void AddElementToOutput(stack ** head, stack ** tail, int number, operation oper)
{

	if (*head != NULL)
	{
		stack * temp = *head;
		while (temp->pNext != NULL)
		{
			temp = temp->pNext;
		}
		temp->pNext = (stack*)malloc(sizeof(stack));
		(*tail) = temp->pNext;
		temp->pNext->value = number;
		temp->pNext->op = oper;
		temp->pNext->pPrev = temp;
		temp->pNext->pNext = NULL;
	}
	else
	{
		*head = (stack*)malloc(sizeof(stack));
		(*head)->value = number;
		(*head)->op = oper;
		(*head)->pNext = NULL;
		(*head)->pPrev = NULL;
	}
}

void ReduceStack(stack ** stack_pointer, operation oper, stack ** out_head_pointer, stack ** out_tail_pointer)
{
	if (oper != close_bracket)
	{
		int a = 0;
		if (oper % 2 == 1)
			a = oper;
		else
			a = oper - 1;
		while ((*stack_pointer) && ((*stack_pointer)->op >= a))
		{
			stack * temp = *stack_pointer;
			AddElementToOutput(out_head_pointer, out_tail_pointer, NULL, temp->op);
			(*stack_pointer) = (*stack_pointer)->pNext;
			free(temp);
		}
	}
	else
	{
		while (*stack_pointer)
		{
			operation temp_oper = (*stack_pointer)->op;
			stack * temp = *stack_pointer;
			(*stack_pointer) = (*stack_pointer)->pNext;
			free(temp);
			if (temp_oper == 1)
				break;
			AddElementToOutput(out_head_pointer, out_tail_pointer, NULL, temp_oper);
		}
	}
}

void PushOperation(stack ** stack_pointer, operation oper, stack ** out_head_pointer, stack ** out_tail_pointer)
{
	if ((*stack_pointer) == NULL)
	{
		*stack_pointer = (stack*)malloc(sizeof(stack));
		(*stack_pointer)->op = oper;
		(*stack_pointer)->pNext = NULL;
	}
	else
	{
		if (oper != 1)
		{
			ReduceStack(stack_pointer, oper, out_head_pointer, out_tail_pointer);
		}
		if (oper != 2)
		{
			if (*stack_pointer)
			{
				stack * temp = *stack_pointer;
				*stack_pointer = (stack*)malloc(sizeof(stack));
				(*stack_pointer)->pNext = temp;
			}
			else
			{
				*stack_pointer = (stack*)malloc(sizeof(stack));
				(*stack_pointer)->pNext = NULL;
			}
			(*stack_pointer)->op = oper;
		}
	}
}

void ClearStack(stack ** stack_pointer, stack ** out_head_pointer, stack ** out_tail_pointer)
{
	while (*stack_pointer)
	{
		stack * temp = *stack_pointer;
		AddElementToOutput(out_head_pointer, out_tail_pointer, NULL, temp->op);
		(*stack_pointer) = (*stack_pointer)->pNext;
		free(temp);
	}
}

void CreatePostfixExpression(char * buffer, stack ** out_head_pointer, stack ** out_tail_pointer, stack ** stack_pointer)
{
	int buffer_length = 0;
	while (buffer[buffer_length] != NULL)
	{
		buffer_length++;
	}
	int j = 0;
	int * ptr = &j;
	for (j; j < buffer_length; j++)
	{
		if ((buffer[j] > 47) && (buffer[j] < 58))
		{
			int number = ReadInt(ptr, buffer);
			AddElementToOutput(out_head_pointer, out_tail_pointer, number, 0);
		}
		else
		{
			operation oper = ReadOperation(ptr, buffer);
			PushOperation(stack_pointer, oper, out_head_pointer, out_tail_pointer);
		}
	}
	ClearStack(stack_pointer, out_head_pointer, out_tail_pointer);
}