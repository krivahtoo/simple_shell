#include "hsh.h"

/**
 * _strcmp - compares two strings.
 *
 * @s1: string 1
 * @s2: string 2
 *
 * Return: 0 = equal, -ve s1 greater, +ve s2 greater
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i])
	{
		if (s1[i] != s2[i])
			break;
		i++;
	}
	return (s1[i] - s2[i]);
}
