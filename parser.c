#include "hsh.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * parse_args - parse arguments replace $ variables
 * @args: arguments passed to cammand
 * @last_status: last command status
 *
 * Return: updated arguments.
 */
char **parse_args(char **args, int last_status)
{
	char **p = args, *name, *value;

	p++; /* ignore command name */
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
					value = to_string(((last_status) & 0xff00) >> 8);
					break;
				default:
					value = _strdup(_getenv(name));
			}
			free(*p);
			*p = _strdup(value);
			free(value);
		}
		p++;
	}

	return (args);
}
