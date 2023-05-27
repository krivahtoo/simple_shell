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
 * set_variables - check if the entry already exists and
 * gives conditions for creation or not
 *
 * @name: name of entry
 * @value: entry value
 * @overwrite: overwrite conditions
 * Return: 0
 */

int set_variables(const char *name, const char *value, int overwrite)
{
	int i;
	char *env_value = NULL, *temp, *new_entry;

	for (i = 0; environ[i] != NULL; i++)
	{
		env_value = _strdup(environ[i]);
		temp = strtok(env_value, "=");

		if (_strncmp(temp, name, _strlen(name)) == 0)
		{
			if (overwrite != 0)
			{
				new_entry = create_entry(name, value);
				if (new_entry == NULL)
					return (-1);

				free(env_value);
				environ[i] = new_entry;
			}
			return (0);
		}
		free(env_value);
		env_value = NULL;
	}
	return (1);
}

/**
 * allocate_env - allocate environ if not allocate
 *
 * Return: 0 on success, -1 on error
 */
int allocate_env(void)
{
	int i = 0;
	char **new_env = NULL;

	while (*(environ + i))
	{
		new_env = _realloc(new_env, i + 1, i + 2);
		*(new_env + i) = _strdup(*(environ + i));
		i++;
	}
	new_env[i] = NULL;
	environ = new_env;
	return (0);
}

/**
 * _setenv - Implementation of the setenv function
 * @name: Name of entry
 * @value: Value associated with entry
 * @overwrite: condition for overwriting value of entry
 * @env_allocated: if env was allocated
 * Return: 0, if successful
 */

int _setenv(
	const char *name,
	const char *value,
	int overwrite,
	int *env_allocated
)
{
	char **new_env, *new_entry, *existing_entry;
	int num_entries = 0, len;

	existing_entry = _getenv(name);
	if (existing_entry != NULL && overwrite == 0)
		return (0);

	new_entry = create_entry(name, value);
	if (new_entry == NULL)
		return (-1);
	if (*env_allocated == 0)
	{
		allocate_env();
		*env_allocated = 1;
	}
	if (existing_entry != NULL)
	{
		set_variables(name, value, overwrite);
		return (0);
	}

	/* Find out how many entries are in environ */
	while (environ[num_entries] != NULL)
		num_entries++;
	len = (num_entries + 2) * sizeof(char *);
	new_env = _realloc(environ, len - 1, len);
	if (environ == NULL)
	{
		free(new_entry);
		return (-1);
	}

	new_env[num_entries + 1] = new_entry;
	new_env[num_entries + 2] = NULL;
	environ = new_env;
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
