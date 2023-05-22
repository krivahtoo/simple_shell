#include "hsh.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_err - print "command not found" error
 *
 * @name: name of our shell ass passed in argv[0]
 * @program: program name the program that was not found
 * @line: line number if it was piped
 */
void print_err(char *name, char *program, int line)
{
	const char *err_str = ": command not found\n";

	(void)line;
	write(STDERR_FILENO, name, strlen(name));
	if (isatty(fileno(stdin)))
		write(STDERR_FILENO, ": ", strlen(": "));
	else
		write(STDERR_FILENO, ": line 1: ", strlen(": line 1: "));
	write(STDERR_FILENO, program, strlen(program));
	write(STDERR_FILENO, err_str, strlen(err_str));
	fflush(stderr);
	if (isatty(fileno(stdin)) == 0)
		exit(127);
}

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

	/* Loop through the string */
	while (1)
	{
		token = strtok(str, delim);
		if (token == NULL)
			break;
		arr = realloc(arr, sizeof(char *) * (i + 2));
		arr[i] = strdup(token);

		str = NULL;
		i++;
	}
	arr[i] = NULL;

	return (arr);
}
