#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hsh.h"

/**
 * _setenv - Implementation of the setenv function
 * @name: Name of entry
 * @value: Value associated with entry
 * @overwrite: condition for overwriting value of entry
 * @ctx: shell context
 * Return: 0, if successful
 */

int _setenv(
	const char *name,
	const char *value,
	int overwrite,
	context_t *ctx
)
{
	node_t *var = get_node(ctx->env, name);

	if (var != NULL && overwrite == 0)
		return (0);

	add_node_end(&ctx->env, name, value);

	return (1);
}

/**
 * _getenv - get env variable
 *
 * @name: variable name
 * @ctx: shell context
 *
 * Return: pointer to string, or NULL
 */
char *_getenv(const char *name, context_t *ctx)
{
	char *ptr = NULL;
	node_t *node;

	node = get_node(ctx->env, name);
	if (node != NULL)
		ptr = node->value;
	return (ptr);
}

/**
 * _unsetenv - remove env variable
 *
 * @name: variable name
 * @ctx: shell context
 *
 * Return: 0 on success, 1 on failure
 */
int _unsetenv(const char *name, context_t *ctx)
{
	return (pop_node(&ctx->env, name));
}

/**
 * allocate_env - allocate new r/w env
 *
 * @ctx: shell context
 */
void allocate_env(context_t *ctx)
{
	int i = 0;
	char *key, *value, *p, *tmp = NULL;

	while (*(environ + i))
	{
		tmp = _strdup(*(environ + i));
		p = tmp;
		key = strtok(tmp, "=");
		if (key != NULL)
		{
			value = strtok(NULL, "=");
			if (value != NULL)
				add_node_end(&ctx->env, key, value);
		}

		free(p);
		i++;
	}
}
