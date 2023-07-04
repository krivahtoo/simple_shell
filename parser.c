#include "hsh.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * parse_commands - parse arguments to commands
 *
 * @ctx: shell context
 * @input: string to parse arguments
 */
void parse_commands(context_t *ctx, char *input)
{
	char **p = NULL;
	char **cmds = split(input, ";");

	p = cmds;
	while (*cmds)
	{
		add_command(&ctx->cmd, *cmds, OP_NONE);
		cmds++;
	}
	free_array(p);
}

/**
 * parse_args - parse arguments replace $ variables
 *
 * @ctx: shell context
 */
void parse_args(context_t *ctx)
{
	node_t *node;
	char **p = ctx->cmd->args, *name, *value;

	if (p == NULL)
		return;

	node = get_node(ctx->aliases, *p);
	/* get alias recursively this could be an alias of alias */
	while (node != NULL)
	{
		free(*p);
		*p = _strdup(node->value);
		node = get_node(ctx->aliases, *p);
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
