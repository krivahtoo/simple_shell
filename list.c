#include "hsh.h"
#include <stdlib.h>

/**
 * to_array - node list to array
 *
 * @h: head node
 *
 * Return: array ponter or null
 */
char **to_array(node_t *h)
{
	char **arr = NULL;
	node_t *node = h;
	int i = 0;

	arr = malloc(sizeof(char *) * 1);
	while (node != NULL)
	{
		arr = _realloc(arr, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
		arr[i] = malloc(
			sizeof(char) * (_strlen(node->key) + _strlen(node->value) + 2)
		);
		_strcpy(arr[i], node->key);
		_strcat(arr[i], "=");
		_strcat(arr[i], node->value);
		node = node->next;
		i++;
	}
	arr[i] = NULL;

	return (arr);
}

/**
 * print_list - prints all the elements of a node_t list.
 *
 * @h: list to print
 *
 * Return: the number of nodes
 */
size_t print_list(const node_t *h)
{
	int len = 0;
	const node_t *node = h;

	while (node != NULL)
	{
		_puts(node->key);
		_putchar('=');
		_puts(node->value);
		_putchar('\n');
		len++;
		node = node->next;
	}

	return (len);
}

/**
 * get_node - returns node with key
 *
 * @head: start node
 * @key: key to check
 *
 * Return: the nth node
 */
node_t *get_node(node_t *head, const char *key)
{
	node_t *node = head;

	while (node != NULL && _strncmp(node->key, key, _strlen(key)) != 0)
	{
		node = node->next;
	}
	return (node);
}

/**
 * pop_node - remove a node
 *
 * @head: start node
 * @key: key to check
 *
 * Return: 0 on success, 1 on failure
 */
size_t pop_node(node_t **head, const char *key)
{
	size_t i = 0;
	node_t *tmp, *old = NULL;

	tmp = *head;
	while (tmp != NULL && _strncmp(tmp->key, key, _strlen(key)) != 0)
	{
		old = tmp;
		tmp = tmp->next;
		i++;
	}
	if (tmp == NULL)
		return (1);
	if (old != NULL)
		old->next = tmp->next;
	else
		*head = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	return (0);
}

/**
 * add_node_end - adds a new node at the end of a listint_t list.
 *
 * @head: start node of the list
 * @key: node key
 * @value: node value
 *
 * Return: the address of the new element, or NULL if it failed
 */
node_t *add_node_end(node_t **head, const char *key, const char *value)
{
	node_t *new, *tmp;

	new = malloc(sizeof(node_t));
	if (new == NULL)
		return (NULL);
	new->key = _strdup(key);
	new->value = _strdup(value);
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	tmp = *head;
	while (tmp->next != NULL && _strncmp(tmp->key, key, _strlen(key)) != 0)
	{
		tmp = tmp->next;
	}
	if (_strncmp(tmp->key, key, _strlen(key)) == 0)
	{
		free_list(&new);
		free(tmp->value);
		tmp->value = _strdup(value);
		new = tmp;
	}
	else
	{
		tmp->next = new;
	}

	return (new);
}
