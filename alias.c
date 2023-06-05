#include "hsh.h"
#include <string.h>

/**
 * print_alias - print alias
 *
 * @alias: alias node
 */
void print_alias(node_t *alias)
{
	_puts(alias->key);
	_putchar('=');
	_putchar('\'');
	_puts(alias->value);
	_putchar('\'');
	_putchar('\n');
}

/**
 * print_aliases - print all aliases
 *
 * @ctx: shell context
 */
void print_aliases(context_t *ctx)
{
	node_t *alias = ctx->aliases;

	while (alias)
	{
		print_alias(alias);
		alias = alias->next;
	}
}

/**
 * set_alias - set a new alias
 *
 * @ctx: shell context
 * @key: alias name
 * @value: alias value
 *
 * Return: 0 on success, 1 on failure
 */
int set_alias(context_t *ctx, const char *key, const char *value)
{
	if (add_node_end(&ctx->aliases, key, value) == NULL)
		return (1);
	return (0);
}

/**
 * get_alias - get an alias
 *
 * @ctx: shell context
 * @key: alias name
 *
 * Return: node_t pointer or null
 */
node_t *get_alias(context_t *ctx, const char *key)
{
	return (get_node(ctx->aliases, key));
}

/**
 * builtin_alias - set or get alias
 *
 * @ctx: shell context
 *
 * Return: 0 on success, -1 on error
 */
int builtin_alias(context_t *ctx)
{
	char *token, *tmp, *value, *p;
	char **args = ctx->args + 1;

	if (*args == NULL)
		print_aliases(ctx);

	while (*args)
	{
		tmp = _strdup(*args);
		p = tmp; /* for free() */
		token = strtok(tmp, "=");
		if (token == NULL)
		{
			free(tmp);
			continue;
		}
		value = strtok(NULL, "=");
		if (value == NULL)
			print_alias(get_alias(ctx, token));
		else
			set_alias(ctx, token, value);
		free(p);
		args++;
	}

	return (0);
}
