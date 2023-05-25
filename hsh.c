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
	int status, line_no = 0, i = 0;

	(void)ac;
	signal(SIGINT, &handler);
	do {
		if (prompt(&input, &len) == EOF)
		{
			if (isatty(fileno(stdin)))
			{
				_puts("\n");
			}
			break;
		}
		if (input != NULL)
		{
			char **args = NULL;
			char *line = input;

			line_no++;
			args = split(strtok(line, "\n"), " ");
			if (exec_builtin(args) == -1 && args != NULL)
			{
				i = execute(args, &status);
				if (i == 1 || i == -2)
					perror(av[0]);
				else if (i == -1)
					break;
			}
			free_array(args);
		}
		free(input);
		len = 0;
		input = NULL;
	} while (1);
	return (WEXITSTATUS(status));
}
