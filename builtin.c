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
 * @exit: exit integer variable
 * @env_allocated: if environ has been allocated
 *
 * Return: 0 on success, -1 failure
 */
int exec_builtin(char **args, int *exit, int *env_allocated)
{
	char *cmd = NULL;
	char *name = NULL, *value = NULL;

	if (args == NULL)
		return (-1);

	cmd = *args;
	if (_strncmp(cmd, "exit", 4) == 0)
	{
		*exit = 1 + _atoi(args[1]);
	}
	else if (_strncmp(cmd, "env", 3) == 0)
		print_env();
	else if (_strncmp(cmd, "setenv", 6) == 0)
	{
		name = args[1];
		value = args[2];
		_setenv(name, value, 1, env_allocated);
	}
	else
		return (-1);
	return (0);
}
