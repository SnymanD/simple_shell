#include "main.h"

/**
 * _eputs - Prints an input string.
 * @str: The string to be printed
 * Return: Void
 */
void _eputs(char *str)
{
	int u = 0;

	if (!str)
		return;
	while (str[u] != '\0')
	{
		_eputchar(str[u]);
		u++;
	}
}

/**
 * _eputchar - Prints the character c to stderr
 * @c: The character to print
 * Return: 1 for Sucess otherwise -1
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1 otherwise -1
 */
int _putfd(char c, int fd)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write(fd, buf, u);
		u = 0;
	}
	if (c != BUF_FLUSH)
		buf[u++] = c;
	return (1);
}

/**
 * _putsfd - Prints an input string
 * @str: String to be printed
 * @fd: FileDescriptor to write to
 * Return: no of chars
 */
int _putsfd(char *str, int fd)
{
	int u = 0;

	if (!str)
		return (0);
	while (*str)
	{
		u += _putfd(*str++, fd);
	}
	return (u);
}
