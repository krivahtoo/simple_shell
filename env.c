#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hsh.h"

/**
 * setenv - Implementation of the setenv function
 * @name: Name of entry
 * @value: Value associated with entry
 * @overwrite: condition for overwriting value of entry
 * Return: 0, if successful
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	char *env_value, *temp, *new_entry, **new_environ;
	int i, num_entries = 0;

	for (i = 0; environ[i] != NULL; i++)
	{
		env_value = strdup(environ[i]);
		temp = strtok(env_value, "=");

		if (strcmp(temp, name) == 0)
		{
			if (overwrite != 0)
			{
				new_entry = malloc(strlen(name) + strlen(value) + 2);
				new_entry = strcat(new_entry, name);
				new_entry = strcat(new_entry, "=");
				new_entry = strcat(new_entry, value);
				environ[i] = new_entry;
			}
			free(env_value);
			return (0);
		}
	}

		new_entry = malloc(strlen(name) + strlen(value) + 2);
		new_entry = strcat(new_entry, name);
		new_entry = strcat(new_entry, "=");
		new_entry = strcat(new_entry, value);

			/* Find out how many entries are in environ */
		while (environ[num_entries] != NULL)
			num_entries++;

		new_environ = (char **)realloc(environ, (num_entries + 2) * sizeof(char *));

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
