#include "general_header.h"

char * ReadFile(FILE * file)
{
	fseek(file, 0, SEEK_END);
	long int file_size = ftell(file);
	fseek(file, 0, 0);
	char * buffer = calloc(file_size + 1, sizeof(char));
	fread(buffer, sizeof(char), file_size, file);
	buffer[file_size] = '\0';
	fclose(file);
	return buffer;
}

int CountLines(char * buffer)
{
	int lines = 1;
	int i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			lines++;
		}
		i++;
	}
	return lines;
}

char ** CreateExpressionsArray(char * buffer, int lines)
{
	char ** rows = calloc(lines, sizeof(char*));
	int Counter = 0;
	for (int i = 0; i < lines; i++)
	{
		int line_length = 0;
		rows[i] = calloc(1, sizeof(char));
		while (buffer[Counter] != '\n')
		{
			if (buffer[Counter] == '\0')
				break;
			line_length++;
			rows[i] = realloc(rows[i], line_length * sizeof(char));
			rows[i][line_length-1] = buffer[Counter];
			Counter++;
		}
		rows[i] = realloc(rows[i], line_length * sizeof(char) + 1);
		rows[i][line_length] = '\0';
		Counter++;
		printf("%s\n", rows[i]);
	}
	return rows;
}

void DeleteList(stack * pHead)
{
	if (pHead)
	{
		DeleteList(pHead->pNext);
		free(pHead);
	}
}