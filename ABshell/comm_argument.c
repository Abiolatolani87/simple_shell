#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_ARGS 16

int main(int argc, char **argv)
{
	char *prompt = "(ABshell) $ ";
	char *lineptr = NULL;
	size_t sizeb = 0;
	ssize_t newchar_read;

	(void)argc;
	(void)argv;

	while (1)

	{
		printf("%s", prompt);

		newchar_read = getline(&lineptr, &sizeb, stdin);

		if (newchar_read == -1)
	{
		perror("getline");
		return (-1);
	}

	/* Split the input line into arguments */

	/*char *args[MAX_ARGS] = {0};*/

	char *arg = strtok(lineptr, " \t\n");
	int num_args = 0;

	while (arg && num_args < MAX_ARGS - 1)

	{
		args[num_args++] = arg;
		arg = strtok(NULL, " \t\n");
	}

	/* Execute the command */
		if (num_args > 0)
	{
		pid_t pid = fork();

		if (pid == -1)
	{
		perror("fork");
	}
		else if (pid == 0)
		{

	/* Child process */

		execvp(args[0], args);
		perror(args[0]);
		exit;
		}
		else
		{
	/* Parent process  */
		waitpid(pid, NULL, 0);
		}

		free(lineptr);
		lineptr = NULL;
		sizeb = 0;
	}
	return (0)
	}
}
