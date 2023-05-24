#include "hsh.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * split - splits a string using a delimiter and returns a
 * malloced array pointer with the last value set to NULL.
 *
 * @str: string to split.
 * @delim: elimiting character to use.
 *
 * Return: malloced array pointer with the last value set to NULL.
 */
char **split(char *str, char *delim)
{
	char **arr = { NULL };
	char *token;
	int i = 0;

	if (str == NULL)
		return (arr);

	/* Loop through the string */
	while (1)
	{
		token = strtok(str, delim);
		if (token == NULL)
			break;
		arr = realloc(arr, sizeof(char *) * (i + 2));
		arr[i] = _strdup(token);

		str = NULL;
		i++;
		arr[i] = NULL;
	}

	return (arr);
}
