#include "shell.h"
/**
 * command_exec - execute a command with its entire path variables.
 * @*data: a pointer to the program's data
 * Return: If sucess zero is returned, otherwise, return -1.
 */
int command_exec(data_of_program *data);
{
	int retrival = 0, status;
	pid_t pidd;

	/* check for program in built ins */
	retrival = builtins_list(data);
	if (retrival != -1)/* if program was found in built ins */
		return (retrival);

	/* check for program file system */
	retrival = find_program(data);
	if (retrival)
	/* if program not found */
	{
		return (retval);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			retrival = exec(data->tokens[0], data->tokens, data->env);
			if (retrival == -1) /* if error when executed*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
