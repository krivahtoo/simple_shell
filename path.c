#include "hsh.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * extract_path - extract directories from PATH variable.
 *
 * @ctx: shell context
 *
 * Return: NULL turminated array
 */
char **extract_path(context_t *ctx)
{
	char *path, *tmp;
	char **paths = { NULL };
	/* Extracts the PATH variable in environ */

	path = _strdup(_getenv("PATH", ctx));
	tmp = path; /* free */
	paths = split(path, ":");
	free(tmp);
	return (paths);
}

/**
 * which - returns path to a binary or NULL
 *
 * @bin: binary name
 * @ctx: shell context
 *
 * Return: full path, NULL when not found
 */
char *which(const char *bin, context_t *ctx)
{
	char *filepath;
	char **paths, **p;
	struct stat buf;

	if (*bin == '/' || *bin == '.')
	{
		if (stat(bin, &buf) == 0)
			return (_strdup(bin));
		else
			return (NULL);
	}

	paths = extract_path(ctx);
	p = paths; /* for free */

	/* Loop through dir paths in PATH */
	while (*paths)
	{
		filepath = malloc(_strlen(*paths) + _strlen(bin) + 2);
		filepath = _strcpy(filepath, *paths);
		filepath = _strcat(filepath, "/");
		filepath = _strcat(filepath, bin);
		if (stat(filepath, &buf) == 0)
		{
			free_array(p);
			return (filepath);
		}

		free(filepath);
		filepath = NULL;
		paths++;
	}
	free_array(p);

	return (NULL);
}
