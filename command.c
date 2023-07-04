#include "hsh.h"

/**
 * free_commands - free command list
 *
 * @head: start of the list
 */
void free_commands(command_t **head)
{
	command_t *node = *head;

	if (node)
	{
		free_commands(&node->next);
		free_array(node->args);
		free(node);
	}
	*head = NULL;
}

/**
 * add_command - add a command node to the end of list
 *
 * @head: start of the list
 * @args: arguments of the command
 * @op: operator
 */
void add_command(command_t **head, const char *args, char op)
{
	command_t *cmd, *tmp;
	char *line;

	cmd = malloc(sizeof(command_t));
	if (cmd == NULL)
		return;
	line = _strdup(args);
	cmd->args = split(line, " ");
	cmd->op = op;
	cmd->next = NULL;
	cmd->name = cmd->args[0];
	tmp = *head;
	if (tmp == NULL)
		*head = cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	free(line);
}

/**
 * next_command - move to the next command
 *
 * @head: start of the list
 *
 * Return: the poped command
 */
command_t *next_command(command_t **head)
{
	command_t *next, *node = *head;

	next = node->next;
	node->next = NULL;
	*head = next;
	return (node);
}
