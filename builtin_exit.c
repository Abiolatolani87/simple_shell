#include "shell.h"

/**
 * builtin_exit - it closes and exit the program with the status
 * @data:the program's data struct
 * Return: zero is returned if sucess, or other number
 * if its declared in the arguments
 */
int builtin_exit(data_of_program *data);
{
	int s;

	if (data->tokens[1] != NULL)
	/*if exists arg for exit, check if is a number*/
		for (s = 0; data->tokens[1][s]; s++)
			if ((data->tokens[1][s] < '0' || data->tokens[1][s] > '9')
				&& data->tokens[1][s] != '+')
			/*if it is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * cd_builtin - change the current directory
 * @data:the program's data struct
 * Return: zero is returned if sucess, or other number
 * if its declared in the arguments
 */
int cd_builtin(data_of_program *data);
{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero is returned if sucess, or other number
 * if its declared in the arguments
 */
int set_work_directory(data_of_program *data, char *new_dir);
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * help_builtin - shows the environment where the shell runs
 * @data: the program's data struct
 * Return: zero is returned if sucess, or other number
 * if its declared in the arguments
 */
int help_builtin(data_of_program *data);
{
	int s, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MSG;
	messages[2] = HELP_ENV_MSG;
	messages[3] = HELP_SETENV_MSG;
	messages[4] = HELP_UNSETENV_MSG;
	messages[5] = HELP_CD_MSG;

	for (s = 0; messages[s]; s++)
	{
		length = str_len(data->tokens[1]);
		if (str_compare(data->tokens[1], messages[s], length))
		{
			_print(messages[s] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero is returned if sucess, or other number
 * if its declared in the arguments
 */
int builtin_alias(data_of_program *data);
{
	int s = 0;

	/* print all environment, if there are no argument*/
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++s])
	{/*set or print each env variable, if there are arguement*/
		if (count_characters(data->tokens[s], "="))
			set_alias(data->tokens[s], data);
		else
			print_alias(data, data->tokens[s]);
	}

	return (0);
}
