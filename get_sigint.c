#include "main.h"

/**
 * get_sigint - Handle signals for the shell process.
 * @sig: Signal handler.
 */

void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
