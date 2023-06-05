#include "hsh.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * parse_args - parse arguments replace $ variables
 * @ctx: shell context
 *
 * Return: updated arguments.
 */
void parse_args(context_t *ctx)
{
	node_t *node;
	char **p = ctx->args, *name, *value;

	if (p == NULL)
		return;

	node = get_node(ctx->aliases, *p);
	if (node != NULL)
	{
		free(*p);
		*p = node->value;
	}
	while (*p)
	{
		if (*p[0] == '$')
		{
			name = (*p) + 1;
			switch (*name)
			{
				case '$':
					value = to_string(getpid());
					break;
				case '?':
					value = to_string(ctx->status);
					break;
				case '\0':
					p++;
					continue;
				default:
					value = _strdup(_getenv(name, ctx));
			}
			free(*p);
			*p = _strdup(value);
			free(value);
		}
		p++;
	}
}
