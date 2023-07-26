#include "main.h"

/**
 * fork_c - forks a an exec to run command
 * @cmd_dat: the parameter
 * Return: nothing (void)
 */
void fork_c(cmd_d *cmd_dat)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(cmd_dat->path, cmd_dat->argv, get_env(cmd_dat)) == -1)
		{
			free_cmd(cmd_dat, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(cmd_dat->status));
		if (WIFEXITED(cmd_dat->status))
		{
			cmd_dat->status = WEXITSTATUS(cmd_dat->status);
			if (cmd_dat->status == 126)
				print_err(cmd_dat, "Permission not granted\n");
		}
	}
}
