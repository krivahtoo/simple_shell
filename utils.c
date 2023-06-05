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
		if (token == NULL || token[0] == '#')
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

/**
 * _atoi - convert a string to an integer.
 *
 * @str: string to convert
 *
 * Return: integer from string
 */
int _atoi(char *str)
{
	int value = 0, sign = 1, i = 0;

	if (str == NULL)
		return (0);

	while (str[i] != '\0')
	{
		if (str[i] == '-')
			sign *= -1;
		else if (str[i] >= '0' && str[i] <= '9')
		{
			if (value == 0)
				value = str[i] - '0';
			else
			{
				value *= 10;
				value += str[i] - '0';
			}
		}
		else
		{
			if (value == 0)
				value = -1;
			break;
		}
		i++;
	}

	return (value * sign);
}

/**
 * to_string - convert integer to string
 *
 * @n: number to convert
 *
 * Return: malloced string pointer or NULL if n < 0
 */
char *to_string(int n)
{
	char *str = NULL, ch;
	int len = 0, i = 0;

	str = malloc(sizeof(char));
	/* using do..while loop to make sure 0 is returned */
	do {
		str = _realloc(str, sizeof(char) * (len + 1), sizeof(char) * (len + 2));
		str[len] = '0' + n % 10;
		n /= 10;
		len++;
	} while (n > 0);
	str[len] = '\0';

	for (i = 0; i < len / 2; i++)
	{
		ch = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = ch;
	}
	return (str);
}
