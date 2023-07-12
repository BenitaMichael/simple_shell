
/**
 * _atoi - converts the initial portion of the string pointed to a integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int a;
	int sign = 1, flag = 0, product;
	unsigned int res = 0;

	for (a = 0; str[a] != '\0' && flag != 2; a++)
	{
		if (str[a] == '-')
			sign *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		product = -res;
	else
		product = res;

	return (product);
}


/**
 * is_alpha - checks for alphabet
 * @c: the input character
 * Return: returns (1) if true and (0) if not
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 * is_delimeter - checks if character is a delimeter
 * @c: the character to check
 * @d: the delimeter
 * Return: returns (1) there is a delimeter, (0) if false
 */
int is_delimeter(char c, char *d)
{
	while (*d)
		if (*d++ == c)
			return (1);
	return (0);
}
