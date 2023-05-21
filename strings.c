#include "hsh.h"
#include <stddef.h>

/**
 * _strlen - Function to get the length of a string
 *
 * @str: string to get length of
 *
 * Return: the length of the string
 */

int _strlen(char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * _strcpy - a function that copies the string pointed to by src into dest
 * @dest: pointer to be copied into
 * @src: pointer to be copied from
 * Return: dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strcat - concatenates two strings.
 * @dest: destination string.
 * @src: source string
 * Return: dest string
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * strncmp - compares the first n bytes of s1 and s2
 * @s1: First string
 * @s2: Second string
 * @n: number of bytes to be compared
 * Return: 0
 */

int strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

		while (i < n)
		{
			if (s1[i] != s2[i])
			{
				/* cast to unsigned char for correct results in all cases */
				return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
			}
			if ((s1[i] == '\0' || s2[i] == '\0'))
				break;
			i++;
		}

		return (0);
}
