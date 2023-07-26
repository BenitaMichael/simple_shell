#include "main.h"

/**
 * shell - main shell loop
 * @cmd_dat: parameter
 * @av: argument vector
 * Return: returns (0) if successful, and (1) if there's an error
 * or an error message
 */

int shell(cmd_d *cmd_dat, char **av)
{
	ssize_t a = 0;
	int _built = 0;

	while (a != -1 && _built != -2)
	{
		clear_cmd(cmd_dat);
		if (interactive_shell(cmd_dat))
			append_S("#Cisfun$ ");
		err_putchar(BUF_FLUSH);
		a = _input(cmd_dat);
		if (a != -1)
		{
			set_cmd(cmd_dat, av);
			_built = find_builtIn(cmd_dat);
			if (_built == -1)
				path_cmd(cmd_dat);
		}
		else if (interactive_shell(cmd_dat))
			_putchar('\n');
		free_cmd(cmd_dat, 0);
	}
	write_history(cmd_dat);
	free_cmd(cmd_dat, 1);
	if (!interactive_shell(cmd_dat) && cmd_dat->status)
		exit(cmd_dat->status);
	if (_built == -2)
	{
		if (cmd_dat->err_num == -1)
			exit(cmd_dat->status);
		exit(cmd_dat->err_num);
	}
	return (_built);
}

/**
 * find_builtIn - checks for built in command
 * @cmd_dat: parameter
 * Return: returns (-1) if builtin command not found, (0) if builtin
 * command is executed successfully
 * and (1) if found but not executed successfully
 */
int find_builtIn(cmd_d *cmd_dat)
{
	int a, ret_builtin = -1;
	builtin_list bl[] = {
		{"exit", exit_cmd},
		{"env", my_env},
		{"help", help_cmd},
		{"history", history_cmd},
		{"setenv", set_environ},
		{"unsetenv", unset_environ},
		{"cd", cd_cmd},
		{"alias", alias_cmd},
		{NULL, NULL}
	};

	for (a = 0; bl[a].type; a++)
		if (my_str_comp(cmd_dat->argv[0], bl[a].type) == 0)
		{
			cmd_dat->len_count++;
			ret_builtin = bl[a].func(cmd_dat);
			break;
		}
	return (ret_builtin);
}

/**
 * path_cmd - checks for a command in PATH
 * @cmd_dat: the parameter & returnstruct
 *
 * Return: void
 */
void path_cmd(cmd_d *cmd_dat)
{
	char *_path = NULL;
	int i, j;

	cmd_dat->path = cmd_dat->argv[0];
	if (cmd_dat->line_flag == 1)
	{
		cmd_dat->len_count++;
		cmd_dat->line_flag = 0;
	}
	for (i = 0, j = 0; cmd_dat->arg[i]; i++)
		if (!is_delimeter(cmd_dat->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	_path = find_full_path(cmd_dat, _get_env(cmd_dat, "PATH="), cmd_dat->argv[0]);
	if (_path)
	{
		cmd_dat->path = _path;
		fork_c(cmd_dat);
	}
	else
	{
		if ((interactive_shell(cmd_dat) || _get_env(cmd_dat, "PATH=")
					|| cmd_dat->argv[0][0] == '/') && if_exec_cmd(cmd_dat, cmd_dat->argv[0]))
			fork_c(cmd_dat);
		else if (*(cmd_dat->arg) != '\n')
		{
			cmd_dat->status = 127;
			print_err(cmd_dat, "No such file\n");
		}
	}
}
