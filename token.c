#include "main.h"

/**
 * **token - splits a string into words and repeated
 * delimeter are ignored
 * @str: string input
 * @delim: delimeter
 * Return: returns the address to a string array
 */

char **token(char *str, char *delim)
{
	int a, b, i, j;
	int word_num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delimeter(str[a], delim) && (is_delimeter(str[a + 1], delim)
					|| !str[a + 1]))
			word_num++;

	if (word_num == 0)
		return (NULL);
	s = malloc((1 + word_num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < word_num; b++)
	{
		while (is_delimeter(str[a], delim))
			a++;
		i = 0;
		while (!is_delimeter(str[a + i], delim) && str[a + i])
			i++;
		s[b] = malloc((i + 1) * sizeof(char));
		if (!s[b])
		{
			for (i = 0; i < b; i++)
				free(s[i]);
			free(s);
			return (NULL);
		}
		for (j = 0; j < i; j++)
			s[b][j] = str[a++];
		s[b][j] = 0;
	}
	s[b] = NULL;
	return (s);
}
