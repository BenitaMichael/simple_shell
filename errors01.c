#include "main.h"

/**
 * err_atoi - converts string inputed to an integer
 * @str: string to be converted
 * Return: returns (0) if no numbers in string,
 * converted number otherwise (-1) on error(res)
 */

int err_atoi(char *str)
{
	int a = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (a = 0;  str[a] != '\0'; a++)
	{
		if (str[a] >= '0' && str[a] <= '9')
		{
			res *= 10;
			res += (str[a] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - prints an error message
 * @cmd_dat: the parameter and return command data struct
 * @str: string (error type)
 * Return: returns (void)
 */

void print_err(cmd_d *cmd_dat, char *str)
{
	append_err_s(cmd_dat->fname);
	append_err_s(": ");
	print_decimal(cmd_dat->line_count, STDERR_FILENO);
	append_err_s(": ");
	append_err_s(cmd_dat->argv[0]);
	append_err_s(": ");
	append_err_s(str);
}

/**
 * print_decimal - prints a decimal number (base 10)
 * @entry: the entry
 * @f_d : file descriptor
 * Return: numbers of char printed
 */

int print_decimal(int entry, int f_d)
{
	int a, num = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int abs, curr;

	if (f_d == STDERR_FILENO)
		__putchar = err_putchar;
	if (entry < 0)
	{
		abs = -entry;
		__putchar('-');
		num++;
	}
	else
		abs = entry;
	curr = abs;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (abs / a)
		{
			__putchar('0' + curr / a);
			num++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	num++;

	return (num);
}


/**
 * rm_comments - replaces '#' with '\0'
 * @buff: string address to be modified
 * Return: returns (0);
 */

void rm_comments(char *buff)
{
	int a;

	for (a = 0; buff[a] != '\0'; a++)
		if (buff[a] == '#' && (!a || buff[a - 1] == ' '))
		{
			buff[a] = '\0';
			break;
		}
}



/**
 * convert_num - converter function, a clone of itoa
 *@no: number
 *@base: parameter
 *@_flags: flags
 * Return: returns the converted result (string)
 */

char *convert_num(long int no, int base, int _flags)
{
	static char *arr;
	static char buf[50];
	char sign = 0;
	char *ptr;
	unsigned long n = no;

	if (!(_flags & CONVERT_UNSIGNED) && no < 0)
	{
		n = -no;
		sign = '-';

	}
	arr = _flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
