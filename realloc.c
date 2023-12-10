#include "s_shell.h"

/**
 * cust_memset - fills memory with a constant byte
 * @dest: the pointer to the memory area
 * @ch: the byte to fill *dest with
 * @n: the amount of bytes to be filled
 * Return: (dest) a pointer to the memory area dest
 */
char *cust_memset(char *dest, char ch, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = ch;
	return (dest);
}

/**
 * cust_free - frees a string of strings
 * @str_arr: string of strings
 */
void cust_free(char **str_arr)
{
	char **temp = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(temp);
}

/**
 * cust_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_sz: byte size of previous block
 * @new_sz: byte size of new block
 *
 * Return: pointer to the reallocated block.
 */
void *cust_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz)
{
	char *p;

	if (!ptr)
		return (malloc(new_sz));
	if (!new_sz)
		return (free(ptr), NULL);
	if (new_sz == old_sz)
		return (ptr);

	p = malloc(new_sz);
	if (!p)
		return (NULL);

	old_sz = old_sz < new_sz ? old_sz : new_sz;
	while (old_sz--)
		p[old_sz] = ((char *)ptr)[old_sz];
	free(ptr);
	return (p);
}
