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
 * putchar_err - print character to stderr
 *
 * @ch: character to print
 *
 * Return: 1 on success.
 */
int putchar_err(char ch)
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
	return (write(STDOUT_FILENO, str, _strlen(str)));
}

/**
 * puts_err - prints a string to stderr.
 *
 * @str: string to print
 *
 * Return: 1 on success.
 */
int puts_err(char *str)
{
	return (write(STDERR_FILENO, str, _strlen(str)));
}

/**
 * print_err - print formatted error message
 *
 * @ctx: shell context
 * @err: error message
 */
void print_err(context_t *ctx, char *err)
{
	puts_err(ctx->name);
	puts_err(": ");
	if (!ctx->isatty)
	{
		putchar_err('0' + ctx->line);
		puts_err(": ");
	}
	if (ctx->cmd)
	{
		puts_err(ctx->cmd->name);
		puts_err(": ");
	}
	puts_err(err);
	fflush(stderr);
}
