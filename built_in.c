#include "main.h"

/**
 * _myhistory - Shows the history list, one command by line.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets alias to the string
 * @info: Parameter structure
 * @str: The string of the alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *s, n;
	int y;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	n = *s;
	*s = 0;
	y = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*s = n;
	return (y);
}

/**
 * set_alias - Sets alias to string
 * @info: Parameter structure
 * @str: The string of the alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *s = NULL, *m = NULL;

	if (node)
	{
		s = _strchr(node->str, '=');
		for (m = node->str; m <= s; m++)
			_putchar(*m);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias builtin function.
 * @info: Structure containing potential arguments.
 *  Return: Always 0 (SUCCESS)
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		s = _strchr(info->argv[x], '=');
		if (s)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
