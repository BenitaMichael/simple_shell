#include "main.h"

/**
 * _free_ptr - frees the pointer address
 * @ptr: pointer address
 * Return: returns (0) if action fails else returns (1)
 */
int _free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
