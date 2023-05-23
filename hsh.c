#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

/**
 * handler - handle system signals
 *
 * @no: signal number
 */
void handler(int no)
{
	(void)no;
	if (isatty(fileno(stdin)))
	{
		_puts("\n#cisfun$ ");
		fflush(stdout);
	}
}

/**
 * main - entry point for simple shell
 *
 * @ac: argument count
 * @av: arguments array
 * @envp: environment values
 *
 * Return: 0 on success, non-zero on failure
 */
int main(int ac, char *av[], char *envp[])
{
	char *input = NULL, *bin = NULL;
	size_t len = 0;
	pid_t child_pid;
	int status, line = 0;

	(void)ac;
	signal(SIGINT, &handler);
	do {
		if (prompt(&input, &len) == EOF)
		{
			_puts("\nexit\n");
			break;
		}
		if (input != NULL)
		{
			char **args = NULL;

			line++;
			args = split(strtok(input, "\n"), " ");
			if (exec_builtin(args) == -1 && args != NULL)
			{
				bin = which(*args);
				if (bin != NULL)
				{
					child_pid = fork();
					if (child_pid == 0)
					{
						if (execve(bin, args, envp) == -1)
							exit(EXIT_FAILURE);
					}
					else if (wait(&status) == -1)
						break;
				}
				else
					print_err(av[0], input, line);
			}
			free_array(args);
		}
	} while (1);
	return (WEXITSTATUS(status));
}
