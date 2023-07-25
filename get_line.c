#include "main.h"

/**
 * input_buf - Buffers chained commands
 * @info: Parameter structure
 * @buf: The address of buffer
 * @len: The address of len
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t u;

	u = 0;

	size_t len_v;

	len_v = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		u = getline(buf, &len_v, stdin);
#else
		u = _getline(info, buf, &len_v);
#endif
		if (u > 0)
		{
			if ((*buf)[u - 1] == '\n')
			{
				(*buf)[u - 1] = '\0';
				u--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = u;
				info->cmd_buf = buf;
			}
		}
	}
	return (u);
}

/**
 * get_input - Gets a line minus the newline
 * @info: Parameter structure
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t u, v, len;
	ssize_t a;

	a = 0;

	char **buf_p = &(info->arg);
	char *p;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &buf, &len);
	if (a == -1)
		return (-1);
	if (len)
	{
		v = u;
		p = buf + u;

		check_chain(info, buf, &v, u, len);
		while (v < len)
		{
			if (is_chain(info, buf, &v))
				break;
			v++;
		}

		u = v + 1;
		if (u >= len)
		{
			u = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (a);
}

/**
 * read_buf - Reads a buffer
 * @info: Parameter structure
 * @buf: buffer
 * @i: size
 * Return: nothing
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a;

	a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}

/**
 * _getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: The address of pointer to ptr buffer
 * @length: Size of preallocated ptr buffer if not NULL
 * Return: Nothing
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t u, len;
	size_t w;
	ssize_t a = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (u == len)
		u = len = 0;

	a = read_buf(info, buf, &len);
	if (a == -1 || (a == 0 && len == 0))
		return (-1);

	c = _strchr(buf + u, '\n');
	w = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + w : w + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + u, w - u);
	else
		_strncpy(new_p, buf + u, w - u + 1);

	s += w - u;
	u = w;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks ctrl-C
 * @sig_num: The signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
