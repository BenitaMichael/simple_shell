#include "main.h"

/**
 * add_node - adds a node to the start of the linked list
 * @h: pointer to head node
 * @str: string field of node
 * @no: node index used by history
 * Return: returns size of linked list
 */

list_s *add_node(list_s **h, const char *str, int no)
{
	list_s *new_h;

	if (!h)
		return (NULL);
	new_h = malloc(sizeof(list_s));
	if (!new_h)
		return (NULL);
	memory_set((void *)new_h, 0, sizeof(list_s));
	new_h->num = no;
	if (str)
	{
		new_h->str = str_duplicate(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->nxt = *h;
	*h = new_h;
	return (new_h);
}

/**
 * add_to_list - adds a node to the list
 * @h: pointer to head node
 * @str: string field of node
 * @no: node index used by history
 * Return: size of list
 */

list_s *add_to_list(list_s **h, const char *str, int no)
{
	list_s *new_nd, *node;

	if (!h)
		return (NULL);

	node = *h;
	new_nd = malloc(sizeof(list_s));
	if (!new_nd)
		return (NULL);
	memory_set((void *)new_nd, 0, sizeof(list_s));
	new_nd->num = no;
	if (str)
	{
		new_nd->str = str_duplicate(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nxt)
			node = node->nxt;
		node->nxt = new_nd;
	}
	else
		*h = new_nd;
	return (new_nd);
}

/**
 * print_list_string - prints only the string element of the list
 * @ptr : pointer to the first node
 * Return: size of linked list
 */

size_t print_list_string(const list_s *ptr)
{
	size_t s = 0;

	while (ptr)
	{
		append_S(ptr->str ? ptr->str : "(nil)");
		append_S("\n");
		ptr = ptr->nxt;
		s++;
	}
	return (s);
}

/**
 * delete_node - deletes node at an index
 * @h: address of pointer to first node
 * @i: index of node to delete
 * Return: returns (1) if deleted and (0) if not
 */

int delete_node(list_s **h, unsigned int i)
{
	list_s *prev, *node;
	unsigned int n = 0;

	if (!h || !*h)
		return (0);

	if (!i)
	{
		node = *h;
		*h = (*h)->nxt;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (n == i)
		{
			prev->nxt = node->nxt;
			free(node->str);
			free(node);
			return (1);
		}
		n++;
		prev = node;
		node = node->nxt;
	}
	return (0);
}

/**
 * free_list - frees the list
 * @h_ptr: pointer to address of head node
 * Return: nothing (void)
 */

void free_list(list_s **h_ptr)
{
	list_s *h, *next, *node;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	node = h;
	while (node)
	{
		next = node->nxt;
		free(node->str);
		free(node);
		node = next;
	}
	*h_ptr = NULL;
}
