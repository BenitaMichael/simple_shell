#include "main.h"

/**
 * get_env - fuction to provide string array copy
 *  of the environment
 * @cmd_dat: Structure type
 * Return: the string array copy of the environment
 */

char **get_env(cmd_d *cmd_dat)
{
	if (!cmd_dat->environ || cmd_dat->env_changed)
	{
		cmd_dat->environ = list_to_str(cmd_dat->env);
		cmd_dat->env_changed = 0;
	}
	/*if (strchr(var, ' ') != NULL)
	 {
		 return (NULL);
	 }*/
	 return (cmd_dat->environ);
}


/**
 * set_env - Initialize a new environment variable,
 *and modify an existing one
 * @cmd_dat: Structure type
 * @var: the string environment variable
 * @v: the string environment variable value
 *  Return: returns (0)
 */

int set_env(cmd_d *cmd_dat, char *var, char *v)
{
	char *buff = NULL, *c;
	list_s *node;

	if (!var || !v)
		return (0);

	buff = malloc(string_length(var) + string_length(v) + 2);
	if (!buff)
		return (1);
	if (strchr(var, ' ') != NULL)
	{
		free (buff);
		return (1);
	}
	my_str_copy(buff, var);
	str_concat(buff, "=");
	str_concat(buff, v);
	node = cmd_dat->env;
	while (node)
	{
		c = _check(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buff;
			cmd_dat->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_to_list(&(cmd_dat->env), buff, 0);
	free(buff);
	cmd_dat->env_changed = 1;
	return (0);
}

/**
 * unset_env - deletes an environment variable
 * @cmd_dat: Structure arguments
 * @var: the string environment variable
 *  Return: returns (1) when delelted, returns (0) otherwise
 */

int unset_env(cmd_d *cmd_dat, char *var)
{
	size_t x = 0;
	list_s *node = cmd_dat->env;
	char *ptr;

	if (!var || !node)
		return (0);

	while (node)
	{
		ptr = _check(node->str, var);
		if (ptr && *ptr == '=')
		{
			cmd_dat->env_changed = delete_node(&(cmd_dat->env), x);
			x = 0;
			node = cmd_dat->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (cmd_dat->env_changed);
}
