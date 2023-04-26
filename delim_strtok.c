#include "shell.h"

/**
 * _strtok - breaks a string line into sub-string.
 *
 * @line: pointer to the string to be broken.
 * @delim: pointer to the string containing the delimeter.
 *
 * Return: A pointer to the first token in the string.
*/

char *_strtok(char *line, char *delim)
{
	int s;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (s = 0; delimeter[s] != '\0'; s++)
		{
			if (*str == delimeter[s])
			break;
		}
		if (delim[s] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (s = 0; delimeter[t] != '\0'; s++)
		{
			if (*str == delimeter[s])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
