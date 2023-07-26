#include "main.h"

/**
 * _strlen - Returns the length of a string
 * @s: String whose length to check
 * Return: Length of the string
 */
int _strlen(char *s)
{
	int x;

	x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;
	return (x);
}

/**
 * _strcmp - Performs lexicogarphic comparison of two strangs.
 * @s1: The 1st string
 * @s2: The 2nd string
 * Return: negative or positive otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if needle starts with haystack
 * @haystack: The string to search
 * @needle: Substring
 * Return: Null or the address
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings
 * @dest: The destination buffer
 * @src: Source buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret;

	ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
