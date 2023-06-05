#include "hsh.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * builtin_env - print enviroment variables
 *
 * @ctx: shell context
 *
 * Return: 0 always
 */
int builtin_env(context_t *ctx)
{
	char **env = ctx->env;

	while (*env)
	{
		_puts(*env);
		_putchar('\n');
		env++;
	}
	return (0);
}

/**
 * builtin_exit - exit builtin command
 *
 * @ctx: shell context
 *
 * Return: 0 always
 */
int builtin_exit(context_t *ctx)
{
	int status = ctx->status;

	if (ctx->args[1] != NULL)
	{
		status = _atoi(ctx->args[1]);
		if (status < 0)
		{
			print_err(ctx, "Illegal number");
			_puts(": ");
			_puts(ctx->args[1]);
			_putchar('\n');
			status = 2;
		}
	}
	free_ctx(ctx);
	exit(status);
	return (0);
}

/**
 * builtin_setenv - change env variable
 *
 * @ctx: shell context
 *
 * Return: 0 always
 */
int builtin_setenv(context_t *ctx)
{
	_setenv(ctx->args[1], ctx->args[2], 1, ctx);
	return (0);
}
