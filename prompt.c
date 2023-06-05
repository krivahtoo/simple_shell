#include "hsh.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

/**
 * prompt - display prompt if not connected to tty and
 * read line from user.
 *
 * @ctx: shell context
 * @stream: file descriptor
 *
 * Return: 0 success, nonzero on failure.
 */
int prompt(context_t *ctx, FILE *stream)
{
	ctx->isatty = isatty(fileno(stream));
	if (ctx->isatty)
	{
		_puts("#cisfun$ ");
		fflush(stdout);
	}

	if (getline(&ctx->buf.ptr, &ctx->buf.len, stream) == EOF)
	{
		return (EOF);
		free_buf(&ctx->buf);
	}
	return (0);
}
