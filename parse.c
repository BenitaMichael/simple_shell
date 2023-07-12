#include "main.h"

/**
 * if_exec_cmd - checks or determine if a
 * file at a given path is an executable command
 * @cmd_dat: the command data struct
 * @path: path to the file
 * Return: (1) if true, (0) if false
 */
int if_exec_cmd(cmd_d *cmd_dat, char *path)
{
	struct stat st;

	(void)cmd_dat;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * char_dup - duplicates characters
 * @path_str: the PATH string
 * @start_c: starting character index
 * @stop_c: stopping charcter index
 * Return: returns pointer to new buffer
 */

char *char_dup(char *path_str, int start_c, int stop_c)
{
	static char buff[1024];
	int i = 0;
	int a = 0;

	for (a = 0, i = start_c; i < stop_c; i++)
		if (path_str[i] != ':')
			buff[a++] = path_str[i];
	buff[a] = 0;
	return (buff);
}

/**
 * find_full_path - finds the full path of an executable command
 * @dat: the data structure
 * @path_str: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of command if found or (NULL) if not
 */
char *find_full_path (cmd_d *dat, char *path_str, char *cmd)
{
	int a = 0, current_p = 0;
	char *_path;

	if (!path_str)
		return (NULL);
	if ((string_length(cmd) > 2) && _check(cmd, "./"))
	{
		if (if_exec_cmd(dat, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[a] || path_str[a] == ':')
		{
			_path = char_dup(path_str, current_p, a);
			if (!*_path)
				str_concat(_path, cmd);
			else
			{
				str_concat(_path, "/");
				str_concat(_path, cmd);
			}
			if (if_exec_cmd(dat, _path))
				return (_path);
			if (!path_str[a])
				break;
			current_p = a;
		}
		a++;
	}
	return (NULL);
}
