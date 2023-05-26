#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hsh.h"

/**
 * create_entry - create a new entry
 * @name: name of entry
 * @value: value associated with entry
 * Return: The new entry created
 */

char *create_entry(const char *name, const char *value)
{
	char *new_entry;

	size_t len = _strlen(name) + _strlen(value) + 2;

	new_entry = malloc(len);
	if (new_entry == NULL)
		return (NULL);

	_strcpy(new_entry, name);
	_strcat(new_entry, "=");
	_strcat(new_entry, value);

	printf("***create entry - %s\n", new_entry);

	return (new_entry);
}

/**
 * setenv_conditions - check if the entry already exists and 
 * gives conditions for creation or not
 *
 * @name: name of entry
 * @overwrie: overwrite conditions
 * Return: 0
 */

int setenv_conditions(const char *name, const char *value, int overwrite)
{
	int i;
	char *env_value, *temp, *new_entry;

	for (i = 0; environ[i] != NULL; i++)
	{
		env_value = _strdup(environ[i]);
		temp = strtok(env_value, "=");

		if (_strncmp(temp, name, _strlen(name)) == 0)
		{
			printf("setenv_conditions - %s\n", env_value);
			free(env_value);
			if (overwrite != 0)
			{
				new_entry = create_entry(name, value);
				if (new_entry == NULL)
					return (-1);

				environ[i] = new_entry;
			}
			return (0);
		}
	}
	return (1);
}

/**
 * _setenv - Implementation of the setenv function
 * @name: Name of entry
 * @value: Value associated with entry
 * @overwrite: condition for overwriting value of entry
 * Return: 0, if successful
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_entry, **new_environ;
	int num_entries = 0, len, existing_entry;

	printf("***%s, %s\n***", name, value);

	existing_entry = setenv_conditions(name, value, overwrite);
	if (existing_entry == 0)
		return (0);

	if (overwrite == 0)
		return (0);

	new_entry = create_entry(name, value);

	printf("new_entry works? = %s\n", new_entry);

	if (new_entry == NULL)
		return (-1);

	/* Find out how many entries are in environ */
	while (environ[num_entries] != NULL)
		num_entries++;

	printf("number of entries in env - %d\n", num_entries);

	len = (num_entries + 2) * sizeof(char *);
	new_environ = _realloc(environ, num_entries, len);

	printf("new_environ realloc works? - %s\n", *new_environ);

	if (new_environ == NULL)
	{
		free(new_entry);
		return (-1);
	}
	new_environ[num_entries + 1] = new_entry;

	printf("new_environ = %s\n", new_environ[num_entries + 1]);

	new_environ[num_entries + 2] = NULL;
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
