#include "main.h"

/**
 * my_getline - reads an entire line from stream from STDIN, An alternative
 * to (geline) function
 * @cmd_dat: struct parameter
 * @ptr: address to the pointer to buffer
 * @len: preallocated ptr buffer size
 * Return: size of preallocated size
 */
int my_getline(cmd_d *cmd_dat, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, l;
	size_t j;
	ssize_t k = 0, s = 0;
	char *p = NULL, *new_ptr = NULL;
	char *c;

	p = *ptr;
	if (p && len)
		s = *len;
	if (i == l)
		i = l = 0;

	k = read_buf(cmd_dat, buf, &l);
	if (k == -1 || (k == 0 && l == 0))
		return (-1);

	c = string_char(buf + i, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : l;
	new_ptr = my_realloc(p, s, s ? s + j : j + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		string_concat(new_ptr, buf + i, j - i);
	else
		string_copy(new_ptr, buf + i, j - i + 1);

	s += j - i;
	i = j;
	p = new_ptr;

	if (len)
		*len = s;
	*ptr = p;
	return (s);
}


/**
 * input_buffer - buffers chained commands
 * @cmd_dat: structure type
 * @buf:  pointer to the buffer
 * @len: address of length variable
 * Return: bytes read
 */
ssize_t input_buffer(cmd_d *cmd_dat, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_t = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signalHandler);
#if USE_GETLINE
		s = getline(buf, &len_t, stdin);
#else
		s = my_getline(cmd_dat, buf, &len_t);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			cmd_dat->line_count_flag = 1;
			rm_comments(*buf);
			build_history(cmd_dat, *buf, cmd_dat->history_count++);
			/* if (string_character(*buf, ';')) is this a command chain? */
			{
				*len = s;
				cmd_dat->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * _input - gets a line minus the newline
 * @cmd_dat: structure type
 * Return: number of bytes read
 */

ssize_t _input(cmd_d *cmd_dat)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j;
	static size_t l;
	ssize_t s = 0;
	char **buf_ptr = &(cmd_dat->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buffer(cmd_dat, &buf, &l);
	if (s == -1) /* EOF */
		return (-1);
	if (l) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		chain_check(cmd_dat, buf, &j, i, l);
		while (j < l) /* iterate to semicolon or end */
		{
			if (is_Chain(cmd_dat, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= l) /* reached end of buffer? */
		{
			i = l = 0; /* reset position and length */
			cmd_dat->cmd_buff_type = CMD_NORM;
		}

		*buf_ptr = p; /* pass back pointer to current command position */
		return (string_length(p)); /* return length of current command */
	}

	*buf_ptr = buf; /* else not a chain, pass back buffer from get_line() */
	return (s); /* return length of buffer from get_line() */
}

/**
 * read_buf - reads an input buffer
 * @cmd_dat: structure type
 * @buf: buffer
 * @s: size of buffer
 * Return: (i)
 */
ssize_t read_buf(cmd_d *cmd_dat, char *buf, size_t *s)
{
	ssize_t i = 0;

	if (*s)
		return (0);
	i = read(cmd_dat->read_file, buf, READ_BUF_SIZE);
	if (i >= 0)
		*s = i;
	return (i);
}


/**
 * signalHandler - blocks ctrl-C from exiting and display
 * a new prompt
 * @sig_num: signal number
 * Return: returns nothing (void)
 */

void signalHandler(__attribute__((unused))int sig_num)
{
	append_S("\n");
	append_S("$ ");
	_putchar(BUF_FLUSH);
}
