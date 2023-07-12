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
		/* TODO: PUT ERROR FUNCTION */
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
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(cmd_dat->stats));
		if (WIFEXITED(cmd_dat->stats))
		{
			cmd_dat->stats = WEXITSTATUS(cmd_dat->stats);
			if (cmd_dat->stats == 126)
				print_err(cmd_dat, "Permission denied\n");
		}
	}
}
