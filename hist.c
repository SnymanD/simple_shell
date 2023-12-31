#include "main.h"

/**
 * get_history_file - Gets the history file.
 * @info: Parameter structure
 * Return: The allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buff;
	char *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - Creates a file, or appends to an existing file
 * @info: Parameter structure
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *file_name;

	list_t *node = NULL;

	file_name = get_history_file(info);

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Reads history from file
 * @info: The parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int u;
	int last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (u = 0; u < fsize; u++)
		if (buf[u] == '\n')
		{
			buf[u] = 0;
			build_history_list(info, buf + last, linecount++);
			last = u + 1;
		}
	if (last != u)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: Buffer
 * @linecount: The history linecount.
 * Return: Always 0 (SUCESS)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Reoders the history linked list after changes.
 * @info: Structure containing potential arguments.
 * Return: The new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int x;

	x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
