#include "shell.h"

/**
* Getline_array - read a single line from the prompt.
* @data:the program's data struct.
*
* Return: reading counting bytes.
*/
int Getline_array(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commd[10] = {NULL};
	static char array_opr[10] = {'\0'};
	ssize_t bytes_read, s = 0;

	/* check if does not exist, more commands in the array */
	/* observe the logical operators */
	if (!array_commd[0] || (array_opr[0] == '&' && errno != 0) ||
		(array_opr[0] == '|' && errno == 0))
	{
		/* the existing memory allocated in the array is fred */
		for (s = 0; array_comm[s]; s++)
		{
			free(array_commd[s]);
			array_commd[s] = NULL;
		}

		/*the file descriptor int to buff is read*/
		bytes_read = read(data->file_dcript, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/*lines splited for \n or ; */
		s = 0;
		do {
			array_commd[s] = str_dup(_strtok(s ? NULL : buff, "\n;"));
			/*check and split for && and || operators*/
			s = check_logic_oprs(array_commd, s, array_opr);
		} while (array_commd[s++]);
	}

	/*obtains the next command (commd 0) and remove it for the array*/
	data->input_line = array_commd[0];
	for (s = 0; array_commd[s]; s++)
	{
		array_commd[s] = array_commd[s + 1];
		array_opr[s] = array_opr[s + 1];
	}

	return (str_len(data->input_line));
}


/**
* check_logic_ops - checks and split for && and || operators
* @array_commd: array of the commands.
* @s: index in the array_commands to be checked
* @array_opr: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commd[], int s, char array_opr[])
{
	char *temp = NULL;
	int r;

	/* checks for the & char in the command line*/
	for (r = 0; array_commd[s] != NULL  && array_commd[s][r]; r++)
	{
		if (array_commd[s][r] == '&' && array_commands[s][r + 1] == '&')
		{
			/*line is splited when chars && was found */
			temp = array_commd[s];
			array_commd[s][r] = '\0';
			array_commd[s] = str_dup(array_commd[s]);
			array_commd[s + 1] = str_dup(temp + r + 2);
			s++;
			array_opr[s] = '&';
			free(temp);
			r = 0;
		}
		if (array_commd[s][r] == '|' && array_commd[s][r + 1] == '|')
		{
			/* line splited when characters || was found */
			temp = array_commd[s];
			array_commd[s][r] = '\0';
			array_commd[s] = str_dup(array_commd[s]);
			array_commd[s + 1] = str_dup(temp + r + 2);
			s++;
			array_opr[s] = '|';
			free(temp);
			r = 0;
		}
	}
	return (s);
}
