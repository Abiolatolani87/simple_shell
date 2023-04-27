#include "shell.h"

/**
 *Expand_buffsize:  expand the buffer size variables
 *@*data: a pointer to a structure of the program's data
 *
 * Return: nothing is returned, but sets errno.
 */
void expand_buffsize(data_of_program *data);
{
	int s, r;
	char line[BUFFER_SIZE] = {0}, expan[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (s = 0; line[s]; s++)
		if (line[s] == '#')
			line[s--] = '\0';
		else if (line[s] == '$' && line[s + 1] == '?')
		{
			line[s] = '\0';
			long_to_string(errno, expan, 10);
			buffer_add(line, expan);
			buffer_add(line, data->input_line + s + 2);
		}
		else if (line[s] == '$' && line[s + 1] == ' ' || line[s + 1] == '$')
		{
			line[s] = '\0';
			long_to_string(getpid(), expan, 10);
			buffer_add(line, expan);
			buffer_add(line, data->input_line + s + 2);
		}
		else if (line[s] == '$' && (line[s + 1] == ' ' || line[s + 1] == '\0'))
			continue;
		else if (line[s] == '$')
		{
			for (r = 1; l	&& lin	!= ' '; r++)
				expan[r - 1] = line[s + r];
			temp = env_get_key(expan, data);
			line[s] = '\0', expan[0] = '\0';
			buffer_add(expan, line + s + r);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expan);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_dup(line);
	}
}

/**
 * expand_alias -it expands aliases
 * @data: a pointer to the program's data struct
 *
 * Return: nothing is returned, but sets errno.
 */
void expand_alias(data_of_program *data);
{
	int s, r was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expan[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (s = 0; line[s]; s++)
	{
		for (r = 0; line[s + r] && line[s + r] != ' '; r++)
			expansion[r] = line[s + r];
		expansion[r] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expan[0] = '\0';
			buffer_add(expan, line + s + r);
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
		data->input_line = str_dup(line);
	}
}

/**
 * buffer_add -to append string at the end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing is returned, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add);
{
	int len, s;

	len = str_len(buffer);
	for (s = 0; str_to_add[s]; s++)
	{
		buffer[len + s] = str_to_add[s];
	}
	buffer[len + s] = '\0';
	return (len + s);
}

