#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

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
 * evaluate - evaluate input
 *
 * @input: intput to evaluate
 * @program: our program name
 * @env_allocated: if environ was malloced
 * @line_no: input lin number
 * @status: child process exit status
 *
 * Return: exit value
 */
int evaluate(
	char *input,
	char *program,
	int *env_allocated,
	int *line_no,
	int *status
)
{
	char **args = NULL;
	char *line = input;
	int i, exit = 0;

	(*line_no)++;
	args = split(strtok(line, "\n"), " ");
	args = parse_args(args, *status);
	if (exec_builtin(args, &exit, env_allocated) == -1 && args != NULL)
	{
		i = execute(args, status);
		if (i == 1)
			print_err(program, *args, *line_no);
		else if (i == -1)
			exit = 1;
	}
	free_array(args);

	return (exit);
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
	int status = 0, line_no = 0, fd = 0;
	int if_exit = 0, env_allocated = 0;
	FILE *stream;

	if (ac >= 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			perror(av[0]);
			exit(127);
		}
		stream = fdopen(fd, "r");
	}
	else
		stream = stdin;
	signal(SIGINT, &handler);
	do {
		if (prompt(&input, &len, stream) == EOF)
		{
			if (isatty(fd))
				_puts("\n");
			if_exit = 1;
		}
		else if (input != NULL)
			if_exit = evaluate(input, av[0], &env_allocated, &line_no, &status);
		free(input);
		len = 0;
		input = NULL;
	} while (!if_exit);
	fclose(stream);
	return (if_exit > 1 ? if_exit - 1 : WEXITSTATUS(status));
}
