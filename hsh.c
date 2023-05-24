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
 *
 * Return: 0 on success, non-zero on failure
 */
int main(int ac, char *av[])
{
	char *input = NULL;
	size_t len = 0;
	int status, line = 0, i = 0;

	(void)ac;
	signal(SIGINT, &handler);
	do {
		if (prompt(&input, &len) == EOF)
		{
			if (isatty(fileno(stdin)))
			{
				_puts("\nexit\n");
			}
			break;
		}
		if (input != NULL)
		{
			char **args = NULL;

			line++;
			args = split(strtok(input, "\n"), " ");
			if (exec_builtin(args) == -1 && args != NULL)
			{
				i = execute(args, &status);
				if (i == 1)
					print_err(av[0], input, line);
				else if (i == -1)
					break;
			}
			free_array(args);
			free(input);
			input = NULL;
			len = 0;
		}
	} while (1);
	return (WEXITSTATUS(status));
}
