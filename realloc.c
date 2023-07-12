#include "main.h"

/**
 * memory_set - fills the memory set with byte
 * @p : pointer to memory
 * @b : bytes 
 * @s : number of byes to be filled
 * Return: (p) the pointer to memory
 */

char *memory_set(char *p, char b, unsigned int s)
{
	unsigned int a;

	for (a = 0; a < s; a++)
		p[a] = b;
	return (p);
}

/**
* str_free - frees an array of strings
* @p: address to string
*/

void str_free(char **p)
{
	char **adr = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(adr);
}

/**
 * my_realloc - (my alternative for realloc) reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @old: byte size of previous block
 * @new: byte size of new block
 * Return: address to previous memory block
 */
void *my_realloc(void *ptr, unsigned int old, unsigned int new)
{
	char *m;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);

	m = malloc(new);
	if (!m)
		return (NULL);

	if (old < new)
	{
    	old = old;
	}
	else
	{
		old = new;
	}

	while (old--)
		m[old] = ((char *)ptr)[old];
	free(ptr);
	return (m);
}
