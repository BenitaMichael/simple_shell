#include "main.h"

/**
 * _set_alias - sets alias to accept string input
 * @cmd_dat: strucyture type
 * @str: the string alias
 * Return: always return (0) if successful and (1) if
 * there's an error
 */

int _set_alias(cmd_d *cmd_dat, char *str)
{
	char *ptr;

	ptr = string_char(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (_unset_alias(cmd_dat, str));

	_unset_alias(cmd_dat, str);
	return (add_to_list(&(cmd_dat->alias), str, 0) == NULL);
}

/**
 * _unset_alias - removes alisas command
 * @cmd_dat: structure type
 * @str: the string alias
 * Return: returns (0) if successful and (1) if unsuccessful
 */
int _unset_alias(cmd_d *cmd_dat, char *str)
{
	char *ptr;
	char a;
	int res;

	ptr = string_char(str, '=');
	if (!ptr)
		return (1);
	a = *ptr;
	*ptr = 0;
	res = delete_node(&(cmd_dat->alias),
		node_index(cmd_dat->alias, start_node(cmd_dat->alias, str, -1)));
	*ptr = a;
	return (res);
}


/**
 * a_print - function toprints an alias string
 * @_node: the alias node
 * Return: returns (0) if successful and (1) if not
 */
int a_print(list_s *_node)
{
	char *ptr = NULL;
	char *a = NULL;

	if (_node)
	{
		ptr = string_char(_node->str, '=');
		for (a = _node->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		append_S(ptr + 1);
		append_S("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_cmd - mimics the alias command
 * @cmd_dat: Structure type
 *  Return: returns (0)
 */
int alias_cmd(cmd_d *cmd_dat)
{
	int a = 0;
	char *ptr = NULL;
	list_s *node = NULL;

	if (cmd_dat->argc == 1)
	{
		node = cmd_dat->alias;
		while (node)
		{
			a_print(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; cmd_dat->argv[a]; a++)
	{
		ptr = string_char(cmd_dat->argv[a], '=');
		if (ptr)
			_set_alias(cmd_dat, cmd_dat->argv[a]);
		else
			a_print(start_node(cmd_dat->alias, cmd_dat->argv[a], '='));
	}

	return (0);
}
