#include "main.h"

/**
 * set_cmd - initialize command structure
 * @cmd_dat: struct type
 * @av: argument vector
 */

void set_cmd(cmd_d *cmd_dat, char **av)
{
	int a = 0;

	cmd_dat->fname = av[0];
	if (cmd_dat->arg)
	{
		cmd_dat->argv = token(cmd_dat->arg, " \t");
		if (!cmd_dat->argv)
		{
			cmd_dat->argv = malloc(2 * sizeof(char *));
			if (cmd_dat->argv)
			{
				cmd_dat->argv[0] = str_duplicate(cmd_dat->arg);
				cmd_dat->argv[1] = NULL;
			}
		}
		for (a = 0; cmd_dat->argv && cmd_dat->argv[a]; a++)
			;
		cmd_dat->argc = a;

		replace_alias(cmd_dat);
		var_replace(cmd_dat);
	}
}

/**
 * clear_cmd - initialize command structure
 * @cmd_dat: structure type
 */

void clear_cmd(cmd_d *cmd_dat)
{
	cmd_dat->arg = NULL;
	cmd_dat->argv = NULL;
	cmd_dat->path = NULL;
	cmd_dat->argc = 0;
}

/**
 * free_cmd - frees command
 * @cmd_dat: structure type
 * @t: returns (Nothing) and true if action is successful
 */

void free_cmd(cmd_d *cmd_dat, int t)
{
	str_free(cmd_dat->argv);
	cmd_dat->argv = NULL;
	cmd_dat->path = NULL;
	if (t)
	{
		if (!cmd_dat->cmd_buf)
			free(cmd_dat->arg);
		if (cmd_dat->env)
			free_list(&(cmd_dat->env));
		if (cmd_dat->history)
			free_list(&(cmd_dat->history));
		if (cmd_dat->alias)
			free_list(&(cmd_dat->alias));
		str_free(cmd_dat->environ);
			cmd_dat->environ = NULL;
		_free_ptr((void **)cmd_dat->cmd_buf);
		if (cmd_dat->readfd > 2)
			close(cmd_dat->readfd);
		_putchar(BUF_FLUSH);
	}
}
