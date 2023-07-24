#include "main.h"

/**
 * is_Chain - test for a chain delimeter
 * @cmd_dat: parameter struct
 * @buff: the character buffer
 * @ptr: pointer to the current position in buf
 * Return: returns (1) if true
 */

int is_Chain(cmd_d *cmd_dat, char *buff, size_t *ptr)
{
	size_t a = *ptr;

	if (buff[a] == '|' && buff[a + 1] == '|')
	{
		buff[a] = 0;
		a++;
		cmd_dat->cmd_buff_type = CMD_OR;
	}
	else if (buff[a] == '&' && buff[a + 1] == '&')
	{
		buff[a] = 0;
		a++;
		cmd_dat->cmd_buff_type = CMD_AND;
	}
	else if (buff[a] == ';')
	{
		buff[a] = 0;
		cmd_dat->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = a;
	return (1);
}

/**
 * chain_check - checks for continue chaining
 * @cmd_dat: the  structure type
 * @buf: the char buffer
 * @adr: current position address in buffer
 * @s: starting position
 * @len: buffer's length
 * Return: returns nothing (void)
 */

void chain_check(cmd_d *cmd_dat, char *buf, size_t *adr, size_t s, size_t len)
{
	size_t p = *adr;

	if (cmd_dat->cmd_buff_type == CMD_AND)
	{
		if (cmd_dat->stats)
		{
			buf[s] = 0;
			p = len;
		}
	}
	if (cmd_dat->cmd_buff_type == CMD_OR)
	{
		if (!cmd_dat->stats)
		{
			buf[s] = 0;
			p = len;
		}
	}

	*adr = p;
}

/**
 * replace_alias - replaces an aliases in the token strings
 * @cmd_dat: the struct type
 * Return: returns (1) if alias is replaced, and (0) if not
 */

int replace_alias(cmd_d *cmd_dat)
{
	int i;
	list_s *node;
	char *c;

	for (i = 0; i < 10; i++)
	{
		node = start_node(cmd_dat->alias, cmd_dat->argv[0], '=');
		if (!node)
			return (0);
		free(cmd_dat->argv[0]);
		c = string_char(node->str, '=');
		if (!c)
			return (0);
		c = str_duplicate(c + 1);
		if (!c)
			return (0);
		cmd_dat->argv[0] = c;
	}
	return (1);
}

/**
 * var_replace - replaces variables
 * @cmd_dat: struct parameter
 * Return: returns (1) if replaced and (0) if not
 */

int var_replace(cmd_d *cmd_dat)
{
	int a = 0;
	list_s *node;

	for (a = 0; cmd_dat->argv[a]; a++)
	{
		if (cmd_dat->argv[a][0] != '$' || !cmd_dat->argv[a][1])
			continue;

		if (!my_str_comp(cmd_dat->argv[a], "$?"))
		{
			replace_str(&(cmd_dat->argv[a]),
					str_duplicate(convert_num(cmd_dat->stats, 10, 0)));
			continue;
		}
		if (!my_str_comp(cmd_dat->argv[a], "$$"))
		{
			replace_str(&(cmd_dat->argv[a]),
					str_duplicate(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = start_node(cmd_dat->env, &cmd_dat->argv[a][1], '=');
		if (node)
		{
			replace_str(&(cmd_dat->argv[a]),
					str_duplicate(string_char(node->str, '=') + 1));
			continue;
		}
		replace_str(&cmd_dat->argv[a], str_duplicate(""));

	}
	return (0);
}

/**
 * replace_str - replaces string
 * @o: pointer to address of old string
 * @n: new string
 * Return: returns (1) if replaced and (0) if not
 */

int replace_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
