#include "main.h"

/**
 * interactive_shell - signifies if the shell is interactive mode
 * @cmd_dat: structure
 * Return: returns (1) if shell is interactive and (0)
 *  if shell is not interactive
 */

int interactive_shell(cmd_d *cmd_dat)
{
	return (isatty(STDIN_FILENO) && cmd_dat->readfd <= 2);
}
