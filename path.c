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
	char **env = environ;
	struct stat buf;

	/* Extracts the PATH variable in envp */
	while (*env)
	{
		if (_strncmp(*env, "PATH", 4) == 0)
		{
			token = strtok(*env, "=");
			if (token == NULL)
				break;
			path = strtok(NULL, "=");
		}
		env++;
	}

	/* Loop through dir paths in PATH */
	while (1)
	{
		token = strtok(path, ":");
		if (token == NULL)
			break;
		filepath = malloc(_strlen(token) + _strlen(bin) + 2);
		filepath = _strcat(filepath, token);
		filepath = _strcat(filepath, "/");
		filepath = _strcat(filepath, bin);
		if (stat(filepath, &buf) == 0)
			return (filepath);

		path = NULL;
	}
	return (NULL);
}
