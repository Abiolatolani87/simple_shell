#include <unistd.h>

/**
 * main - programmes that print 'A-Z' in uppercase
 *
 * Return: Always 0;
 *
 */

int main(void)
{
	char *alpha =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
	int ac = 27;
	{
		write(STDOUT_FILENO, alpha, ac);
	}
	return (0);
}
