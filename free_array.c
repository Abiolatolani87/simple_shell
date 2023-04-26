#include "shell.h"

/**
 * free_recurrent_data - free the fields needed each loop
 * @data: pointer to a struct of the program's data
 * Return: Nothing
 */

void free_recurrent_data(data_of_program *data)
{
	if (data->tokens)
		free_array_f_pointers(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: pointer to a struct of the program's data
 * Return: Nothing
 */

void free_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recurrent_data(data);
	free_array_f_pointers(data->env);
	free_array_f_pointers(data->alias_list);
}

/**
 * free_array_of_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: Nothing
 */

void free_array_f_pointers(char **array)
{
	int r;

	if (array != NULL)
	{
		for (r = 0; array[r]; r++)
			free(array[r]);

		free(array);
		array = NULL;
	}
}
