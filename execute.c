#include "hsh.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute - execute a program with arguments
 *
 * @ctx: shell context
 *
 * Return: 0 on success, 1 on command not found, -1 on failure
 */
int execute(context_t *ctx)
{
	char *bin;
	pid_t child_pid;
	int status = 0;
	char **env = to_array(ctx->env);

	bin = which(*ctx->args, ctx);
	if (bin == NULL)
	{
		free_array(env);
		free(bin);
		return (1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		free(bin);
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(bin, ctx->args, env) == -1)
			_exit(EXIT_FAILURE);
	}
	else
	{
		if (wait(&status) == -1)
		{
			free_array(env);
			free(bin);
			return (-1);
		}
		ctx->status = WEXITSTATUS(status);
	}

	free_array(env);
	free(bin);
	return (0);
}

/**
 * exec_builtin - execute a built in command
 *
 * @ctx: shell context
 *
 * Return: 0 on success, -1 failure
 */
int exec_builtin(context_t *ctx)
{
	int i = 0;
	builtin_t bltns[] = {
		{"env", builtin_env},
		{"exit", builtin_exit},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{NULL, NULL}
	};

	if (ctx->args == NULL)
		return (-1);

	for (; bltns[i].name != NULL; i++)
		if (_strcmp(bltns[i].name, *ctx->args) == 0)
			return (bltns[i].f(ctx));
	return (-1);
}
