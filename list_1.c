#include "main.h"

/**
 * list_len - Determines length of linked list
 * @h: The pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t y;

	y = 0;

	while (h)
	{
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * list_to_strings - Returns an array of strings of the list.
 * @head: The pointer to first node.
 * Return: The array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t u = list_len(head);
	size_t v;
	char **strs;
	char *str;

	if (!head || !u)
		return (NULL);
	strs = malloc(sizeof(char *) * (u + 1));
	if (!strs)
		return (NULL);
	for (u = 0; node; node = node->next, u++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (v = 0; v < u; v++)
				free(strs[v]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[u] = str;
	}
	strs[u] = NULL;
	return (strs);
}


/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: The pointer to first node.
 * Return: The size of list.
 */

size_t print_list(const list_t *h)
{
	size_t i;

	i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - Returns node whose string starts with prefix
 * @node: The pointer to list head.
 * @prefix: The string to match
 * @c: The next character after prefix to match
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p;

	p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node
 * @head: The pointer to list head.
 * @node: The pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i;

	i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
