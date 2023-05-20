#include "../hsh.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *name = "HELLO";
	char *value = "world";
	int overwrite = 1;
	int return_set;

	return_set = _setenv(name, value, overwrite);

	if (return_set == -1)
		return (EXIT_FAILURE);

	while (*environ != NULL)
	{
		printf("%s", *environ);
		environ++;
	}
	return (0);
}
