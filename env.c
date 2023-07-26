#include "main.h"

/**
 * _myenv - Prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment
 * Return: The value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *s;

	while (node)
	{
		s = starts_with(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int u;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (u = 1; u <= info->argc; u++)
		_unsetenv(info, info->argv[u]);

	return (0);
}

/**
 * populate_env_list - Populates env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0 (SUCESS)
 */
int populate_env_list(info_t *info)
{
	list_t *node;

	size_t i;

	node = NULL;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
