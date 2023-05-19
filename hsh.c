#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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
	char *input = NULL;
	char *bin = NULL;
	size_t len = 0;
	pid_t child_pid;
	int i, status;

	(void)ac;
	(void)av;
	do {
		/**
		 * TODO: check if it is connected to a terminal.
		 * i.e. not executed with `echo "/bin/ls" | ./hsh`
		 * don't show prompt when not connected
		 */
		if (isatty(fileno(stdin)))
		{

			printf("#cisfun$ ");
			fflush(stdout);
		}

		i = getline(&input, &len, stdin);
		if (i == EOF)
		{
			break;
		}
		if (input != NULL)
		{
			bin = which(strtok(input, "\n"));
			if (bin != NULL)
			{
				child_pid = fork();
				if (child_pid == 0)
				{
					/* TODO: use split to split arguments */
					char *args[] = { NULL, NULL };

					args[0] = bin;
					if (execve(args[0], args, envp) == -1)
					{
						perror("Executing command failed");
						exit(EXIT_FAILURE);
					}
					break;
				}
				else if (wait(&status) == -1)
					break;
			}
		}
	} while (1);

	return (WEXITSTATUS(status));
}
