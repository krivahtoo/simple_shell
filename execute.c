#include "hsh.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute - execute a program with arguments
 *
 * @args: arguments args[0] is the program name
 * @status: command return status
 *
 * Return: 0 on success, 1 on command not found, -1 on failure
 */
int execute(char **args, int *status)
{
	char *bin;
	pid_t child_pid;
	char **env = environ;

	bin = which(*args);
	if (bin != NULL)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(bin, args, env) == -1)
				exit(EXIT_FAILURE);
		}
		else if (wait(status) == -1)
		{
			free(bin);
			return (1);
		}
	}
	else
		return (1);
	free(bin);
	return (0);
}
