#include "helpers.h"

/**
 * print_enviro - prints environment variables
 * @env: environment
 * Return: void
 */

void print_enviro(char **env)
{
	size_t run = 0;

	while (env[run])
	{
		write(STDOUT_FILENO, env[run], strlen(env[run]));
		write(STDOUT_FILENO, "\n", 1);
		run++;
	}
}

/**
 * end_file - terminate
 * @myline:last  line inserted
 * Return: void
 */
void end_file(char *myline)
{
	(void)myline;
}

