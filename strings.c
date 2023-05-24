#include "hsh.h"

/**
 * _strlen - Function to get the length of a string
 *
 * @str: string to get length of
 *
 * Return: the length of the string
 */

int _strlen(const char *str)
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

char *_strcat(const char *dest, const char *src)
{
	int dest_len = 0, src_len = 0, i, j;
	char *final_str = NULL;

	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}

	while (src[src_len] != '\0')
	{
		src_len++;
	}

	final_str = (char *)malloc((dest_len + src_len + 1) * sizeof(char));

	if (final_str == NULL)
		return (NULL);

	for (i = 0; i < dest_len; i++)
		final_str[i] = dest[i];

	for (j = 0; j < src_len; j++)
		final_str[i + j] = src[j];

	final_str[i + j] = '\0';

	return (final_str);
}

/**
 * _strncmp - compares the first n bytes of s1 and s2
 * @s1: First string
 * @s2: Second string
 * @n: number of bytes to be compared
 * Return: 0
 */

int _strncmp(const char *s1, const char *s2, size_t n)
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

/**
 * _strdup - Function to duplicate string
 * @str: String to be duplicated
 *
 * Return: NULL if str is NULL, NULL if insufficient memory
 * Pointer to str duplicate
 */

char *_strdup(const char *str)
{
	int i, len = 0;
	char *s;

	if (str == NULL)
	{
		return (NULL);
	}

	while (str[len] != '\0')
	{
		len++;
	}

	s = malloc(sizeof(*s) * (len + 1));
	if (s == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < len; i++)
	{
		s[i] = str[i];
	}
	s[len] = '\0';
	return (s);
}
