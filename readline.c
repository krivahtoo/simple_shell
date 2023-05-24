#include "hsh.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _getline - scan for a line from stdin
 *
 * @str: pointer to string to store the string
 * @len: pointer to len
 * @stream: io stream to scan
 *
 * Return: number of chars
 */
ssize_t _getline(char **str, size_t *len, FILE *stream)
{
	char ch;
	int fd = fileno(stream);
	int i;
	ssize_t count = 0;

	if (*str == NULL && *len == 0)
	{
		*str = malloc(sizeof(char) * (*len) + 1);
		if (*str == NULL)
			return (-1);
	}
	i = read(fd, &ch, sizeof(ch));
	while (ch != '\n')
	{
		if (i == -1 || ch == '\0')
			return (-1);
		count += i;
		*(*str + (*len)) = ch;
		*len += 1;
		*str = _realloc(*str, *len, (*len) + 1);
		if (*str == NULL)
			return (-1);
		i = read(fd, &ch, sizeof(ch));
	}
	return (count);
}
