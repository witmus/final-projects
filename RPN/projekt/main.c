#include "general_header.h"
#include "parsing.h"
#include "computing.h"
#include "outputRPN.h"
#include "input_analysis.h"
#include "vld.h"

int main(int argc, char * argv[])
{
	if (argv[1])
	{
		if (argv[1][0] == 'p')
		{
			FILE * in_file = fopen("info.txt", "r");
			FILE * out_file = fopen("output.txt", "w");
			if (in_file == NULL)
			{
				puts("input file error\n");
				return 1;
			}
			char * buffer = ReadFile(in_file);
			int lines = CountLines(buffer);
			printf("LINES: %d\n", lines);
			char ** expressions_array = CreateExpressionsArray(buffer, lines);
			free(buffer);
			fclose(in_file);
			for (int j = 0; j < lines; j++)
			{
				stack * pHead = NULL;
				stack ** head_pointer = &pHead;
				stack * pTail = NULL;
				stack ** tail_pointer = &pTail;
				stack * stos = NULL;
				stack ** stos_ptr = &stos;
				stack * computing_stack = NULL;
				stack ** computing_ptr = &computing_stack;
				CreatePostfixExpression(expressions_array[j], head_pointer, tail_pointer, stos_ptr);
				CalculateExpressions(head_pointer, computing_ptr);
				WriteRPN(pHead);
				FILE_WriteRPN(pHead, out_file);
				printf("VALUE: %.3f\n", computing_stack->value);
				fprintf(out_file, "VALUE: %.3f\n", computing_stack->value);
				DeleteList(pHead);
				DeleteList(computing_stack);
				free(expressions_array[j]);
			}
			free(expressions_array);
			fclose(out_file);
		}
		else if (argv[1][0] == 'k')
		{
			int licznik = 0;
			char * buffer = (char*)malloc(sizeof(char));
			char temp;
			while ((temp = getchar()) != '\n')
			{
				buffer = realloc(buffer, (licznik + 2) * sizeof(char));
				buffer[licznik] = temp;
				licznik++;
			}
			buffer = realloc(buffer, (licznik + 2) * sizeof(char));
			buffer[licznik] = '\0';
			stack * pHead = NULL;
			stack ** head_pointer = &pHead;
			stack * pTail = NULL;
			stack ** tail_pointer = &pTail;
			stack * RPN_stack = NULL;
			stack ** stack_ptr = &RPN_stack;
			stack * computing_stack = NULL;
			stack ** computing_ptr = &computing_stack;
			CreatePostfixExpression(buffer, head_pointer, tail_pointer, stack_ptr);
			CalculateExpressions(head_pointer, computing_ptr);
			WriteRPN(pHead);
			printf("VALUE: %.3f\n", computing_stack->value);
			free(computing_stack);
			DeleteList(pHead);
			free(buffer);
		}
	}
	return 0;
}