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
 * @ctx: shell context
 *
 * Return: exit value
 */
int evaluate(context_t *ctx)
{
	char *line = ctx->buf.ptr;
	int i, exit = 0;

	(ctx->line)++;
	ctx->args = split(strtok(line, "\n"), " ");
	parse_args(ctx);
	if (exec_builtin(ctx) == -1 && ctx->args != NULL)
	{
		i = execute(ctx);
		if (i == 1)
			print_err(ctx, "not found\n");
		else if (i == -1)
			exit = 1;
	}
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
	int if_exit = 0, fd = 0;
	context_t ctx = { NULL, 0,  NULL, NULL, { NULL, 0 }, 0, 0};
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
	allocate_env(&ctx);
	ctx.name = av[0];
	do {
		free_buf(&ctx.buf);
		if (prompt(&ctx, stream) == EOF)
		{
			if (ctx.isatty)
				_puts("\n");
			if_exit = 1;
		}
		else if (ctx.buf.ptr != NULL)
			if_exit = evaluate(&ctx);
		free_array(ctx.args);
		ctx.args = NULL;
	} while (!if_exit);
	free_ctx(&ctx);
	fclose(stream);
	return (ctx.status);
}
