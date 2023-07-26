#include "main.h"

/**
 * _strcpy - Copies a string
 * @dest:destination
 * @src: source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int x;

	x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: String to duplicate
 * Return: Pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length;
	char *ret;

	length = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Prints an input string
 * @str: String to be printed
 * Return: NULL
 */
void _puts(char *str)
{
	int x;

	x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - Writes the character c to stdout
 * @c: The character to print
 * Return: 1 (SUCCESS) otherwise 0
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
