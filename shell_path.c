#include "shell.h"

int check_fileperm(char *full_path);

/**
 * find_progpath - find a program in the path
 * @data: a pointer to the data of the program
 * Return: 0 is returned if success, errcode otherwise
 */

int find_progpath(data_of_program *data)
{
	int s = 0, ret_code = 0;
	char **directories;

	if (!data->commd_name)
		return (2);

	/*check if is a full_path or an executable in the same path */
	if (data->commd_name[0] == '/' || data->commd_name[0] == '.')
		return (check_file(data->commd_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_dup("/"), data->commd_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (s = 0; directories[s]; s++)
	{/* appends the function_name to path */
		directories[s] = str_concat(directoriess[s], data->tokens[0]);
		ret_code = check_file(directories[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has executable*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_dup(directories[s]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories is returned
 */

char **tokenize_path(data_of_program *data)
{
	int s = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_dup(PATH);

	/* find the number of directories in the PATH */
	for (s = 0; PATH[s]; s++)
	{
		if (PATH[s] == ':')
			counter_directories++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/*tokenize and duplicate each token of path*/
	s = 0;
	tokens[s] = str_dup(_strtok(PATH, ":"));
	while (tokens[s++])
	{
		tokens[s] = str_dup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_fileperm - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 is returned on success, or error code if it exits.
 */

int check_fileperm(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exit the file*/
	errno = 127;
	return (127);
}
