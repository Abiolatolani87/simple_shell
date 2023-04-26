#include "shell.h"

/**
 * tokenize - tokenizes a command string into individual arguments
 *
 * @data: a pointer to the program's data.
 *
 * Return: an array of the different parts of the string
 */

void tokenize(data_of_program *data)
{
	char *delimiter = " \t";
	int r, s, counter = 2, length;

	length = str_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (r = 0; data->input_line[r]; r++)
	{
		for (r = 0; delimiter[r]; r++)
		{
			if (data->input_line[r] == delimiter[r])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	r = 0;
	data->tokens[r] = str_duplicate(_strtok(data->input_line, delimiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[r++])
	{
		data->tokens[r] = str_duplicate(_strtok(NULL, delimiter));
	}
}
