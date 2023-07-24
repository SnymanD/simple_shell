#include "main.h"

/**
 **_strncpy - Copies a string
 *@dest: Destination string to be copied to
 *@src: The source string
 *@n: The amount of characters to be copied
 *Return: str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int u, v;
	char *s = dest;

	u = 0;
	while (src[u] != '\0' && u < n - 1)
	{
		dest[u] = src[u];
		u++;
	}
	if (u < n)
	{
		v = u;
		while (v < n)
		{
			dest[v] = '\0';
			v++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates two strings (Add two strings)
 *@dest: The 1st string
 *@src: The 2nd string
 *@n: The amount of bytes to be maximally used
 *Return: The concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int u, v;
	char *s = dest;

	u = 0;
	v = 0;
	while (dest[u] != '\0')
		u++;
	while (src[v] != '\0' && v < n)
	{
		dest[u] = src[v];
		u++;
		v++;
	}
	if (v < n)
		dest[u] = '\0';
	return (s);
}

/**
 **_strchr - Locates a character in a string
 *@s: The string to be parsed
 *@c: The character to look for
 *Return: A pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
