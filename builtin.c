#include "hsh.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * print_env - print enviroment variables
 */
void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		_puts(*env);
		_putchar('\n');
		env++;
	}
}

/**
 * exec_builtin - execute a built in command
 *
 * @args: arguments passed by the user
 *
 * Return: 0 on success, -1 failure
 */
int exec_builtin(char **args)
{
	char *cmd = NULL;

	if (args == NULL)
		return (-1);

	cmd = *args;
	if (_strncmp(cmd, "exit", 4) == 0)
	{
		free_array(args);
		exit(0);
	}
	else if (_strncmp(cmd, "env", 3) == 0)
		print_env();
	else
		return (-1);
	return (0);
}
