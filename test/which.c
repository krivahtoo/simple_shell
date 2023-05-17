#include "../hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - entry point
 *
 * Return: 0 always
 */
int main(void)
{
	char *binpath = NULL;

	binpath = which("cat");
	if (binpath == NULL)
		perror("does not exist in path");
	else
	{
		printf("found at: %s\n", binpath);
	}
	free(binpath);

	return (0);
}
