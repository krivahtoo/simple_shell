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

	return (new_entry);
}

/**
 * set_variables - check if the entry already exists and
 * gives conditions for creation or not
 *
 * @name: name of entry
 * @value: entry value
 * @overwrite: overwrite conditions
 * @ctx: shell context
 * Return: 0
 */

int set_variables(
	const char *name,
	const char *value,
	int overwrite,
	context_t *ctx
)
{
	int i;
	char *new_entry;

	for (i = 0; ctx->env[i] != NULL; i++)
	{
		if (_strncmp(ctx->env[i], name, _strlen(name)) == 0)
		{
			if (overwrite != 0)
			{
				free(ctx->env[i]);
				new_entry = create_entry(name, value);
				if (new_entry == NULL)
					return (-1);

				ctx->env[i] = new_entry;
			}
			return (0);
		}
	}
	return (1);
}

/**
 * allocate_env - allocate new r/w env
 *
 * @ctx: shell context
 */
void allocate_env(context_t *ctx)
{
	int i = 0;

	ctx->env = malloc(sizeof(char *) * 1);
	while (*(environ + i))
	{
		ctx->env = _realloc(
			ctx->env,
			sizeof(char *) * (i + 1),
			sizeof(char *) * (i + 2)
		);
		*(ctx->env + i) = _strdup(*(environ + i));
		i++;
	}
	*(ctx->env + i) = NULL;
}

/**
 * _setenv - Implementation of the setenv function
 * @name: Name of entry
 * @value: Value associated with entry
 * @overwrite: condition for overwriting value of entry
 * @ctx: shell context
 * Return: 0, if successful
 */

int _setenv(
	const char *name,
	const char *value,
	int overwrite,
	context_t *ctx
)
{
	char *new_entry, *existing_entry;
	int len = 0;

	existing_entry = _getenv(name, ctx);
	if (existing_entry != NULL)
	{
		if (overwrite == 0)
			return (0);
		set_variables(name, value, overwrite, ctx);
		return (0);
	}

	new_entry = create_entry(name, value);
	if (new_entry == NULL)
		return (-1);

	/* Find out how many entries are in environ */
	while (ctx->env[len] != NULL)
		len++;
	ctx->env = _realloc(
		ctx->env,
		sizeof(char *) * (len + 1),
		sizeof(char *) * (len + 2)
	);
	if (ctx->env == NULL)
	{
		free(new_entry);
		return (-1);
	}

	ctx->env[len] = new_entry;
	ctx->env[len + 1] = NULL;
	return (0);
}

/**
 * _getenv - get env variable
 *
 * @name: variable name
 * @ctx: shell context
 *
 * Return: pointer to string, or NULL
 */
char *_getenv(const char *name, context_t *ctx)
{
	char **env = ctx->env;
	char *ptr = NULL;

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
