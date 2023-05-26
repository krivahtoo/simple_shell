#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hsh.h"

/**
 * _setenv - Implementation of the setenv function
 * @name: Name of entry
 * @value: Value associated with entry
 * @overwrite: condition for overwriting value of entry
 * Return: 0, if successful
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	char *env_value, *temp, *new_entry, **new_environ;
	int i, num_entries = 0, len;

	for (i = 0; environ[i] != NULL; i++)
	{
		env_value = _strdup(environ[i]);
		temp = strtok(env_value, "=");
		if (_strncmp(temp, name, _strlen(name)) == 0)
		{
			if (overwrite != 0)
			{
				new_entry = malloc(_strlen(name) + _strlen(value) + 2);
				new_entry = _strcat(new_entry, name);
				new_entry = _strcat(new_entry, "=");
				new_entry = _strcat(new_entry, value);
				environ[i] = new_entry;
			}
			free(env_value);
			return (0);
		}
	}

	new_entry = malloc(_strlen(name) + _strlen(value) + 2);
	new_entry = _strcat(new_entry, name);
	new_entry = _strcat(new_entry, "=");
	new_entry = _strcat(new_entry, value);
	/* Find out how many entries are in environ */
	while (environ[num_entries] != NULL)
		num_entries++;
	len = (num_entries + 1) * sizeof(char *);
	new_environ = (char **)_realloc(environ, len, len + i);
	if (new_environ == NULL)
	{
		free(new_entry);
		return (-1);
	}
	new_environ[num_entries] = new_entry;
	new_environ[num_entries + 1] = NULL;
	environ = new_environ;
	return (0);
}

/**
 * _getenv - get env variable
 *
 * @name: variable name
 *
 * Return: pointer to string, or NULL
 */
char *_getenv(const char *name)
{
	char **env = environ;
	char *ptr = NULL;
	/* Extracts the PATH variable in environ */
	while (*env)
	{
		if (_strncmp(*env, name, _strlen(name)) == 0)
		{
			ptr = *env;
			while (*ptr != '=' && *ptr != '\0')
				ptr++;
			if (*ptr == '=')
				ptr++;
			else
				ptr = NULL;
			break;
		}
		env++;
	}
	return (ptr);
}
