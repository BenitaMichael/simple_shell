#include "main.h"

/**
 * string_length - function to return the length of a string
 * @str: the string whose length would be checked
 * Return: the lenght of string input
 */
size_t string_length(char *str)
{
	int len = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * str_concat - concatenates two string input
 * @adr: the address of buffer destination
 * @ssrc: the sourse of the buffer
 * Return: returns the address to destination buffer
 */
char *str_concat(char *adr, char *ssrc)
{
	char *des = adr;

	while (*adr)
		adr++;
	while (*ssrc)
		*adr++ = *ssrc++;
	*adr = *ssrc;
	return (des);
}



/**
 * my_str_comp - compares two string input
 * @s1: the first string input
 * @s2: the second string input
 * Return: negative if s1 < s2, positive if s1 > s2,
 * (0) if s1 s2 are the same
 */
int my_str_comp(const char *s1, const char *s2)
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
	else if (*s1 < *s2)
	{
		return(-1);
	}else
	{
		return (1);
	}
}



/**
 * _check - checks if needle starts with haystack
 * @haystack: string input to search
 * @needle: substring to find
 * Return: returns NULL or pointer of the next character of haystack
 */
char *_check(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

