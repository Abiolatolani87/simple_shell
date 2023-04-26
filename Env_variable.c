#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int s, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_length = str_len(key);

	for (s = 0; data->env[s]; s++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[s], key_length) &&
		 data->env[s][key_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[s] + key_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int s, key_length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (s = 0; data->env[s]; s++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[s], key_length) &&
		 data->env[s][key_length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->env[s]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[s] = str_concat(str_duplicate(key), "=");
	data->env[s] = str_concat(data->env[s], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[s + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int s, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (s = 0; data->env[s]; s++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[s], key_length) &&
		 data->env[s][key_length] == '=')
		/* if key already exists, remove them */
		{
			free(data->envs[s]);

			/* move the others keys one position down */
			s++;
			for (; data->env[s]; s++)
			{
				data->env[s - 1] = data->env[s];
			}
			/* put the NULL value at the new end of the list */
			data->env[s - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int r;

	for (r = 0; data->env[r]; r++)
	{
		_print(data->env[r]);
		_print("\n");
	}
}
