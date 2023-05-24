#include "hsh.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * _putchar - print character to screen
 *
 * @ch: character to print
 *
 * Return: 1 on success.
 */
int _putchar(char ch)
{
	return (write(STDERR_FILENO, &ch, 1));
}

/**
 * _puts - prints a string.
 *
 * @str: string to print
 *
 * Return: 1 on success.
 */
int _puts(char *str)
{
	return (write(STDERR_FILENO, str, _strlen(str)));
}

/**
 * print_err - print "command not found" error
 *
 * @name: name of our shell ass passed in argv[0]
 * @program: program name the program that was not found
 * @line: line number if it was piped
 */
void print_err(char *name, char *program, int line)
{
	char *err_str = ": command not found\n";

	(void)line;
	_puts(name);
	if (isatty(fileno(stdin)))
		_puts(": ");
	else
	{
		_puts(": line ");
		_putchar('0' + line);
		_puts(": ");
	}
	_puts(program);
	_puts(err_str);
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
