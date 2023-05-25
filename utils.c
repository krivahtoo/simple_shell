#include "hsh.h"
#include <stddef.h>
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
	size_t len;

	if (str == NULL)
		return (arr);

	/* Loop through the string */
	while (1)
	{
		token = strtok(str, delim);
		if (token == NULL)
			break;
		if (i == 0)
			len = 0;
		else
			len = sizeof(char *) * (i + 1);
		arr = _realloc(arr, len, sizeof(char *) * (i + 2));
		arr[i] = _strdup(token);

		str = NULL;
		i++;
		arr[i] = NULL;
	}

	return (arr);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 *
 * @ptr: pointer to memory previously allocated with
 * a call to malloc
 * @old_size: the size, in bytes, of the allocated space for ptr
 * @new_size: the new size, in bytes of the new memory block
 *
 * Return: ponter to reallocated memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p = NULL;
	unsigned int i = 0;

	if (old_size == new_size)
		return (ptr);

	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	p = malloc(new_size);
	if (p != NULL && ptr != NULL)
	{
		for (i = 0; i < old_size; i++)
			*((char *)p + i) = *((char *)ptr + i);
		free(ptr);
	}
	return (p);
}
