#include "main.h"

/**
 * _memset - Fills the memory with a constant byte
 * @s: The pointer to the memory area
 * @b: The byte to fill *s with
 * @n: The amount of bytes to be filled
 * Return: A pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int x;

	x = 0;

	for (; x < n; x++)
		s[x] = b;
	return (s);
}

/**
 * ffree - Frees a string of strings
 * @pp: String of strings
 */
void ffree(char **pp)
{
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}

/**
 * _realloc - Reallocates a block of memory
 * @ptr: Pointer to previous malloc'ated block
 * @old_size: The byte size of previous block
 * @new_size: The byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
