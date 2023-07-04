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
	print_list(ctx->env);
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

	if (ctx->cmd->args[1] != NULL)
	{
		status = _atoi(ctx->cmd->args[1]);
		if (status < 0)
		{
			print_err(ctx, "Illegal number");
			puts_err(": ");
			puts_err(ctx->cmd->args[1]);
			putchar_err('\n');
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
 * Return: 0 on success, 1 on error
 */
int builtin_setenv(context_t *ctx)
{
	char *name = ctx->cmd->args[1];
	char *value = ctx->cmd->args[2];

	if (name != NULL && value != NULL)
		return (_setenv(name, value, 1, ctx));
	return (1);
}

/**
 * builtin_unsetenv - change env variable
 *
 * @ctx: shell context
 *
 * Return: 0 on success, 1 on error
 */
int builtin_unsetenv(context_t *ctx)
{
	char *name = ctx->cmd->args[1];

	if (name != NULL)
		return (_unsetenv(name, ctx));
	return (1);
}

/**
 * builtin_cd - command to change directory
 *
 * @ctx: shell context
 *
 * Return: 0 on success, 1 on error
 */
int builtin_cd(context_t *ctx)
{
	char *tmp = NULL, *path = NULL;

	if (ctx->cmd->args[1] == NULL)
		path = _strdup(_getenv("HOME", ctx));
	else if (*(ctx->cmd->args[1]) == '-')
	{
		path = _strdup(_getenv("OLDPWD", ctx));
		_puts(path);
		_putchar('\n');
	}
	else
		path = _strdup(ctx->cmd->args[1]);
	tmp = getcwd(tmp, 100);
	if (chdir(path) == -1)
	{
		free(path);
		free(tmp);
		return (1);
	}
	_setenv("OLDPWD", tmp, 1, ctx);
	_setenv("PWD", path, 1, ctx);

	free(tmp);
	free(path);
	return (0);
}
