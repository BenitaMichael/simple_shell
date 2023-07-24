#include "main.h"

/**
 * append_err_s - prints an input string
 * @s: the error string to be printed
 * Return: returns nothing (void)
 */
void append_err_s(char *s)
{
	int a = 0;

	if (!s || s == NULL)
		return;
	while (s[a] != '\0')
	{
		err_putchar(s[a]);
		a++;
	}
}

/**
 * err_putchar - writes the character c to stderr
 * @c: The character to print
 * Return: If successful (1) while if an error occurs,
 * (-1) is returned, and errno is set appropriately
 */

int err_putchar(char c)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 * fd_putc - writes the character to given file
 * @c: The printed character
 * @f_d: The filedescriptor to write to
 * Return: If successful (1), if there is an error (-1) is returned,
 * and errno is set appropriately
 */

int fd_putc(char c, int f_d)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(f_d, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 * fd_puts - prints an input string in the file descriptor
 * @s: the string to be printed
 * @f_d: the filedescriptor to write to
 * Return: returns the character inputted
 */
int fd_puts(char *s, int f_d)
{
	int a = 0;

	if (!s)
		return (0);
	while (*s)
	{
		a += fd_putc(*s++, f_d);
	}
	return (a);
}
