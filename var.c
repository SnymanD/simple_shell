#include "main.h"

/**
 * is_chain - Test if current char in buffer is a chain delimeter
 * @info: Parameter struct
 * @buf: The char buffer
 * @p: Current Position
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t s = *p;

	if (buf[s] == '|' && buf[s + 1] == '|')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[s] == '&' && buf[s + 1] == '&')
	{
		buf[s] = 0;
		s++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[s] == ';')
	{
		buf[s] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = s;
	return (1);
}

/**
 * check_chain - Checks we should continue chaining based on last status
 * @info: The parameter structure
 * @buf: Character buffer
 * @p: current position in buf
 * @i: initial position in buf
 * @len: length of buffer
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t s = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			s = len;
		}
	}

	*p = s;
}

/**
 * replace_alias - Replaces an aliases in the tokenized string
 * @info: Info
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *node;
	char *p;

	x = 0;

	for (; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces vars in the tokenized string
 * @info: Parameter structure
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i;
	list_t *node;

	i = 0;

	for (; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces string
 * @old: THE Address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
