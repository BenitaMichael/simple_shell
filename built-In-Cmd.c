#include "main.h"

/**
 * exit_cmd - exit command for the shell
 * @cmd_dat: structure
 * Return: (1) exits, returns (0) if cmd_dat.argv[0] != "exit".
 */
int exit_cmd(cmd_d *cmd_dat)
{
	int e_check;

	if (cmd_dat->argv[1])
	{
		e_check = err_atoi(cmd_dat->argv[1]);
		if (e_check == -1)
		{
			cmd_dat->status = 2;
			print_err(cmd_dat, "Incorrect number: ");
			append_err_s(cmd_dat->argv[1]);
			err_putchar('\n');
			return (1);
		}
		cmd_dat->err_num = err_atoi(cmd_dat->argv[1]);
		return (-2);
	}
	cmd_dat->err_num = -1;
	return (-2);
}

/**
 * help_cmd - gives information on changed directories
 * @cmd_dat: Structure containing arguments
 * Return: returns (0)
 */

int help_cmd(cmd_d *cmd_dat)
{
	char **arg_arr;

	arg_arr = cmd_dat->argv;
	append_S("Function does not exist \n");
	if (0)
	{
		append_S(*arg_arr);
	}
	return (0);
}


/**
 * cd_cmd - changes directories
 * @cmd_dat: Structure containing potential arguments
 * Return: returns (0)
 */

int cd_cmd(cmd_d *cmd_dat)
{
	char *c, *d; /* d stands for directory */
	char buff[1024];
	int _chdir;

	c = getcwd(buff, 1024);
	if (!c)
		append_S("TODO: >>getcwd failure emsg here<<\n");
	if (!cmd_dat->argv[1])
	{
		d = _get_env(cmd_dat, "HOME=");
		if (!d)
			_chdir = chdir((d = _get_env(cmd_dat, "PWD=")) ? d : "/");
		else
			_chdir = chdir(d);
	}
	else if (my_str_comp(cmd_dat->argv[1], "-") == 0)
	{
		if (!_get_env(cmd_dat, "OLDPWD="))
		{
			append_S(c);
			_putchar('\n');
			return (1);
		}
		append_S(_get_env(cmd_dat, "OLDPWD=")), _putchar('\n');
		_chdir = chdir((d = _get_env(cmd_dat, "OLDPWD=")) ? d : "/");
	}
	else
		_chdir = chdir(cmd_dat->argv[1]);
	if (_chdir == -1)
	{
		print_err(cmd_dat, "can't cd to ");
		append_err_s(cmd_dat->argv[1]), err_putchar('\n');
	}
	else
	{
		set_env(cmd_dat, "OLDPWD", _get_env(cmd_dat, "PWD="));
		set_env(cmd_dat, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * history_cmd - displays the history list
 * @cmd_dat: Structure
 *  Return: returns (0)
 */
int history_cmd(cmd_d *cmd_dat)
{
	prints_element(cmd_dat->history);
	return (0);
}
