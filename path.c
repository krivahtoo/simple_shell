#include "hsh.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * which - returns path to a binary or NULL
 *
 * @bin: binary name
 *
 * Return: full path, NULL when not found
 */
char *which(const char *bin)
{
	char *path, *token, *filepath;
	char **env = environ, *tmp;
	struct stat buf;

	if (bin[0] == '/' || bin[0] == '.')
	{
		if (stat(bin, &buf) == 0)
			return (strdup(bin));
		else
			return (NULL);
	}

	/* Extracts the PATH variable in envp */
	while (*env)
	{
		if (strncmp(*env, "PATH", 4) == 0)
		{
			tmp = strdup(*env); /* don't modify env variable */
			token = strtok(tmp, "=");
			if (token == NULL)
				break;
			path = strtok(NULL, "=");
			break;
		}
		env++;
	}

	/* Loop through dir paths in PATH */
	while (1)
	{
		token = strtok(path, ":");
		if (token == NULL)
			break;
		filepath = malloc(strlen(token) + strlen(bin) + 2);
		filepath = strcat(filepath, token);
		filepath = strcat(filepath, "/");
		filepath = strcat(filepath, bin);
		if (stat(filepath, &buf) == 0)
			return (filepath);

		path = NULL;
	}
	return (NULL);
}
