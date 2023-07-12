#include "main.h"

/**
 * _get_env - gets the value of an environment variables
 * @cmd_dat: Structure  arguments
 * @name: environment variable name
 * Return: the value of environment
 */
char *_get_env(cmd_d *cmd_dat, const char *name)
{
	list_s *node = cmd_dat->env;
	char *a;

	while (node)
	{
		a = _check(node->str, name);
		if (a && *a)
			return (a);
		node = node->nxt;
	}
	return (NULL);
}

/**
 * my_env - prints the current environment
 * @cmd_dat: Structure type
 * Return: returns(0)
 */
int my_env(cmd_d *cmd_dat)
{
	print_list_string(cmd_dat->env);
	return (0);
}

/**
 * set_environ - Initialize a new environment variable,
 * and modify an existing one
 * @cmd_dat: Structure type.
 *  Return: returns (0)
 */
int set_environ(cmd_d *cmd_dat)
{
	if (cmd_dat->argc != 3)
	{
		append_err_s("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(cmd_dat, cmd_dat->argv[1], cmd_dat->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_environ - deletes an environment variable
 * @cmd_dat: Structure arguments
 * Return: return (0)
 */
int unset_environ(cmd_d *cmd_dat)
{
	int a;

	if (cmd_dat->argc == 1)
	{
		append_err_s("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= cmd_dat->argc; a++)
		unset_env(cmd_dat, cmd_dat->argv[a]);

	return (0);
}

/**
 * populate_env - populates environment linked list
 * @cmd_dat: Structure type
 * Return: returns environment list
 */

int populate_env(cmd_d *cmd_dat)
{
	list_s *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node(&node, environ[a], 0);
	cmd_dat->env = node;
	return (0);
}
