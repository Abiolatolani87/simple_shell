#include "shell.h"

/**
 * expand_variables - Expand variables
 * @data: Pointer to  struct of the program's data
 *
 * Return: Returns nothing, but sets errno.
 */
void expand_variables(data_of_program *data);
{
	int s, r;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (s = 0; line[s]; s++)
		if (line[s] == '#')
			line[s--] = '\0';
		else if (line[s] == '$' && line[s + 1] == '?')
		{
			line[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + s + 2);
		}
		else if (line[s] == '$' && line[s + 1] == '$')
		{
			line[s] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + i + 2);
		}
		else if (line[s] == '$' && (line[s + 1] == ' ' || line[s + 1] == '\0'))
			continue;
		else if (line[s] == '$')
		{
			for (s = 1; line[s + r] && line[s + r] != ' '; r++)
				expansion[r - 1] = line[s + r];
			temp = env_get_key(expansion, data);
			line[s] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + s + r);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - Expand aliases
 * @data: A pointer to a struct of the program's data
 *
 * Return: Returns nothing, but sets errno.
 */
void expand_alias(data_of_program *data);
{
	int s, r, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (s = 0; line[s]; s++)
	{
		for (r = 0; line[s + r] && line[s + r] != ' '; j++)
			expansion[r] = line[s + r];
		expansion[r] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + s + r);
			line[s] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add);
{
	int length, char s;

	length = strnlen(setbuffer);
	for (s = 0; strtold[s]; s++)
	{
		buffer[length + s] = str_to_add[s];
	}
	buffer[length + s] = '\0';
	return (length + s);
}

