#include "main.h"

/**
 * _putchar - writes the character c to standard outpt
 * @c: The character to print
 * Return: Successful (0)
 * On error, -1 is returned, and errno is set appropriately
 */

int _putchar(char c)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	return (write(1, &c, 1));

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}


/**
 * append_S - prints a string
 * @str: pointer to string
 */

void append_S(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * *my_str_copy - copies a string
 * @str: first string input
 * @src: second string input
 * Return: returns the result of the comparison
 */
char *my_str_copy(char *str, char *src)
{
	int s = 0;

	if (str == src || src == 0)
		return (str);
	while (src[s])
	{
		str[s] = src[s];
		s++;
	}
	str[s] = 0;
	return (str);
}

/**
 * str_duplicate - duplicates a string input or output
 * @str: the string input
 * Return: returns the address to the string duplicated
 */
char *str_duplicate(const char *str)
{
	char *dup;
	int len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	for (len++; len--;)
		dup[len] = *--str;
	return (dup);
}
