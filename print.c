#include "hsh.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * _putchar - print character to screen
 *
 * @ch: character to print
 *
 * Return: 1 on success.
 */
int _putchar(char ch)
{
	return (write(STDOUT_FILENO, &ch, 1));
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
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * print_err - print "command not found" error
 *
 * @ctx: shell context
 * @err: error message
 */
void print_err(context_t *ctx, char *err)
{
	_puts(ctx->name);
	_puts(": ");
	if (!ctx->isatty)
	{
		_putchar('0' + ctx->line);
		_puts(": ");
	}
	_puts(ctx->args[0]);
	_puts(": ");
	_puts(err);
	fflush(stderr);
	ctx->status = 127;
}
