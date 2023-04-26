#include "shell.h"

/**
 * List_builtins - search for match and execute the associate builtin
 * @data:the program's data struct
 * Return: Returns the return of the function executed if there is a match,
 * otherwise returns -1
 */
int list_builtins(data_of_program *data);
{
	int iterator;
	builtins options[] = {
		{"exit", exit_buitin},
		{"help", help_builtin},
		{"cd", cd_builtin},
		{"alias", alias_ builtin},
		{"env", env_ builtin},
		{"setenv", set_env_builtin},
		{"unsetenv", unset_env_builtin},
		{NULL, NULL}
	};

/*walk the structure through*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*if the given command and a builtin match*/
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[iterator].function(data));
		}
/*return -1 if there is no match*/
	}
	return (-1);
}

