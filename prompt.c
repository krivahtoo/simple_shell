#include "hsh.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

/**
 * prompt - display prompt if not connected to tty and
 * read line from user.
 *
 * @input: where to store the input
 * @len: where to store the input len
 * @fd: file descriptor
 *
 * Return: 0 success, nonzero on failure.
 */
int prompt(char **input, size_t *len, FILE *stream)
{
	if (isatty(fileno(stream)))
	{
		_puts("#cisfun$ ");
		fflush(stdout);
	}

	if (getline(input, len, stream) == EOF)
	{
		return (EOF);
		free(input);
	}
	return (0);
}
