#include "shell.h"

/**
 * printman_alias - add, remove or show aliases
 * @data: for the program's data struct
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int printman_alias(data_of_program *data, char *alias)
{
	int s, r, alias_len;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = str_len(alias);
		for (s = 0; data->alias_list[s]; s++)
		{
			if (!alias || (str_compare(data->alias_list[s], alias, alias_len)
				&&	data->alias_list[s][alias_len] == '='))
			{
				for (r = 0; data->alias_list[s][r]; r++)
				{
					buffer[r] = data->alias_list[s][r];
					if (data->alias_list[s][r] == '=')
						break;
				}
				bufferr[r + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[s] + r + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);

/**
 *get_alias - add, remove or show aliases
 * @data: for the program's data struct
 * @name: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int s, alias_len;

	/* it validates the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_len = str_len(name);

	for (s = 0; data->alias_list[s]; s++)
	{/* It iterates through the environ and check for closeness of the varname */
		if (str_compare(name, data->alias_list[s], alias_len) &&
			data->alias_list[s][alias_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[s] + alias_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias -it adds, or override alias
 * @alias_str: alias to be set in the form (name='value')
 * @data:the program's data struct
 * Return: zero is returned if sucess, or other number
 * if its declared in the arguments
 */
int set_alias(char *alias_str, data_of_program *data)
{
	int s, r;
	char buffer[250] = {'0'}, *temp = NULL;

	/*it  validate the arguments */
	if (alias_str == NULL ||  data->alias_list == NULL)
		return (1);
	/* It iterates alias to find = char */
	for (s = 0; alias_str[s]; s++)
		if (alias_str[s] != '=')
			buffer[s] = alias_str[s];
		else
		{/*it searches if the value of the alias is another alias */
			temp = get_alias(data, alias_str + s + 1);
			break;
		}

	/* It iterates through the alias list and check for varname closeness*/
	for (r = 0; data->alias_list[r]; r++)
		if (str_compare(buffer, data->alias_list[r], s) &&
			data->alias_list[s][r] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[r]);
			break;
		}

	/* it adds the alias */
	if (temp)
	{/* if the alias exist already */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[r] = str_dup(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[r] = str_dup(alias_string);
	return (0);
}
