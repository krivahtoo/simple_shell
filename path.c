#include "hsh.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * extract_path - extract directories from PATH variable.
 *
 * Return: NULL turminated array
 */
char **extract_path(void)
{
	char **env = environ, *tmp, *token;
	char **paths = { NULL };
	/* Extracts the PATH variable in environ */
	while (*env)
	{
		if (_strncmp(*env, "PATH", 4) == 0)
		{
			tmp = _strdup(*env); /* don't modify env variable */
			token = strtok(tmp, "=");
			if (token == NULL)
				break;
			paths = split(strtok(NULL, "="), ":");
			free(tmp);
			break;
		}
		env++;
	}
	return (paths);
}

/**
 * free_array - free paths from PATH
 *
 * @paths: NULL terminated array of paths
 */
void free_array(char **paths)
{
	int i = 0;

	if (paths)
	{
		while (paths[i])
			free(paths[i++]);
		free(paths);
	}
}

/**
 * which - returns path to a binary or NULL
 *
 * @bin: binary name
 *
 * Return: full path, NULL when not found
 */
char *which(const char *bin)
{
	char *filepath = NULL;
	char **paths, **p;
	struct stat buf;

	if (*bin == '/' || *bin == '.')
	{
		if (stat(bin, &buf) == 0)
			return (_strdup(bin));
		else
			return (NULL);
	}

	paths = extract_path();
	p = paths; /* for free */

	/* Loop through dir paths in PATH */
	while (*paths)
	{
		filepath = malloc(_strlen(*paths) + _strlen(bin) + 2);
		filepath = _strcpy(filepath, *paths);
		filepath = _strcat(filepath, "/");
		filepath = _strcat(filepath, bin);
		if (stat(filepath, &buf) == 0)
			return (filepath);

		free(filepath);
		filepath = NULL;
		paths++;
	}
	free_array(p);

	return (NULL);
}
