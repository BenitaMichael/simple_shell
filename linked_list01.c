#include "main.h"

/**
 * list_length - determines length of linked list
 * @ptr: pointer to first node
 * Return: returns the size of linked list
 */
size_t list_length(const list_s *ptr)
{
	size_t s = 0;

	while (ptr)
	{
		ptr = ptr->next;
		s++;
	}
	return (s);
}

/**
 * list_to_str - array of strings is returned
 * @h: pointer to head node
 * Return: returns an array of strings
 */

char **list_to_str(list_s *h)
{
	list_s *node = h;
	size_t l = list_length(h);
	size_t i;
	char **string;
	char *str;

	if (!h || !l)
		return (NULL);
	string = malloc(sizeof(char *) * (l + 1));
	if (!string)
		return (NULL);
	for (l = 0; node; node = node->next, l++)
	{
		str = malloc(string_length(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < l; i++)
				free(string[i]);
			free(string);
			return (NULL);
		}

		str = my_str_copy(str, node->str);
		string[l] = str;
	}
	string[l] = NULL;
	return (string);
}


/**
 * prints_element - prints all elements of a linked list
 * @h: pointer to head node
 * Return: returns the size of list
 */

size_t prints_element(const list_s *h)
{
	size_t s = 0;

	while (h)
	{
		append_S(convert_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		append_S(h->str ? h->str : "(nil)");
		append_S("\n");
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * start_node - identifies the string with prefix
 * @node: pointer to head node
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: returns either a match or nothing
 */

list_s *start_node(list_s *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = _check(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - gets the index of a node
 * @h: pointer to node list
 * @n: pointer to the node
 * Return: returns the index of node or -1
 */
ssize_t node_index(list_s *h, list_s *n)
{
	size_t s = 0;

	while (h)
	{
		if (h == n)
			return (s);
		h = h->next;
		s++;
	}
	return (-1);
}
