#ifndef _MAIN_H_
#define _MAIN_H_

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/**
*typedef void(*sighandler_t)(int)
*sighandler_t signal(int signum, sighandler_t handler);
*int close(int fd);
*int access(const char *pathname, int mode);
*int chdir(const char *path);
*int clisedir(DIR *dirp);
*int execve(cont char *pathname, char *const argv[], char *const envp[]);
*void exit(int status);
*void _exit(int status);
*int fflush(FILE *stream);
*pid_t fork(void);
*void free(void *ptr);
*char *getcwd(char *buf, size_t size);
*ssize_t getline(char **lineptr, size_t *n, FILE *stream);
*pid_t getpid(void);
*int isatty(int fd);
*int kill(pid_t pid, int sig);
*int open(const char *pathname, int flags, mode_t mode);
*DIR *opendir(const char *name);
*void perror(const char *s);
*ssize_t read(int fd, void *buff size_t count);
*struct dirent *readdir(DIR *dirp);
*ssize_t write(int fd,  const void *buf, size_t count);
*pid_t wait3(int wstatus, int option, struct rusage *rusage);
*pid_t wait4(pid_t pid, int *wstatus, int option, struct rusage *rusage);
*pid_t wait(int *wstatus);
*pid_t waitpid(pid_t pid, int *wstatus, int option);
*char *strtok(char *str, const char *delim);
*int stat(const char *pathname, struct stat *statbuf);
*/

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststring - singly linked list
 * @num: the number field
 * @str: a string
 * @nxt: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_s;
/**
 * struct cmd_dat - linked list created
 * @arg: pointer to strings with arguments
 * @argv: pointer to an array of strings
 * @path: string path
 * @argc: argument count (command-line arguments)
 * @line_count: characters count in a string
 * @err_num: error code
 * @linecount_flag: flag to count line of string inputs
 * @fname: pointer to program file
 * @readfd: file descriptor used for reading inputs
 * @env: linked list of environ variables
 * @environ: array of environ variables
 * @env_changed: checks for if environment has changed
 * @history: pointer to past entry
 * @histcount: memory for prev command entered
 * @status: result from prev command
 * @alias: command aliases
 * @cmd_buf: pointer address to command buffer
 * @cmd_buf_type: command buffer (CMD_type: || 0r &&, )
 */
typedef struct cmddata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_s *env;
	list_s *history;
	list_s *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type; /* accepts ||, &&, ; */
	int readfd;
	int histcount;
} cmd_d;

#define CMDDATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string function
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(cmd_d *);
} builtin_list;


/* string function(s) */
int _putchar(char);
void append_S(char *str); /*appends strings from character*/
size_t string_length(char *str);
int my_str_comp(const char *, const char *);
int replace_str(char **o, char *n);
char *str_concat(char *adr, char *ssrc);
char *my_str_copy(char *str, char *src);
char *str_duplicate(const char *str);
char *_check(const char *haystack, const char *needle);


/*fork function(s)*/
void fork_c(cmd_d *cmd_dat);

/* simple shell loop functions */
int shell(cmd_d *, char **);
int find_builtIn(cmd_d *);
void path_cmd(cmd_d *);

/* parse functions */
int if_exec_cmd(cmd_d *, char *);
char *char_dup(char *, int, int);
char *find_full_path(cmd_d *, char *, char *);


/* error functions */
void append_err_s(char *);
int err_putchar(char);
int fd_putc(char c, int fd);
int fd_puts(char *str, int fd);
int err_atoi(char *s);
void print_err(cmd_d *, char *);
int print_decimal(int entry, int f_d);
char *convert_num(long int no, int base, int _flags);
void rm_comments(char *buff);


/* exit functions */
char *string_char(char *ptr, char s);
char *string_copy(char *dest, char *src, int n); /*Still working on it*/
char *string_concat(char *dest, char *src, int n);

/* free function(s) */
int _free_ptr(void **);

/* interactive shell function(s) */
int interactive_shell(cmd_d *);

/* _atoi functions */
int _atoi(char *str);
int is_alpha(int c);
int is_delimeter(char c, char *d);

/* alias function(s) */
int _set_alias(cmd_d *, char *str);
int _unset_alias(cmd_d *, char *str);
int a_print(list_s *_node);
int alias_cmd(cmd_d *);

/* token function(s) */
char **token(char *str, char *delim);

/* built in command function */
int exit_cmd(cmd_d *);
int history_cmd(cmd_d *);
int help_cmd(cmd_d *);
int cd_cmd(cmd_d *);

/* memory allocation functions (realloc) */
char *memory_set(char *, char, unsigned int);
void str_free(char **);
void *my_realloc(void *, unsigned int, unsigned int);


/* environ functions */
char **get_env(cmd_d *);
int set_env(cmd_d *, char *, char *); /* still confusing */
int unset_env(cmd_d *, char *);

/* environment functions */
char *_get_env(cmd_d *, const char *);
int my_env(cmd_d *);
int set_environ(cmd_d *);
int unset_environ(cmd_d *);
int populate_env(cmd_d *);

/* history functions */
char *history_file(cmd_d *);
int rd_history(cmd_d *);
int write_history(cmd_d *);
int build_history(cmd_d *, char *buf, int line_count);
int number_history(cmd_d *);


/* getline functions (my getline functions) */
int my_getline(cmd_d *, char **, size_t *);
ssize_t input_buffer(cmd_d *, char **buf, size_t *);
ssize_t read_buf(cmd_d *, char *buf, size_t *);
ssize_t _input(cmd_d *);
void signalHandler(int);

/* command data functions */
void set_cmd(cmd_d *, char **av);
void clear_cmd(cmd_d *);
void free_cmd(cmd_d *, int t);

/* linked list functions */
list_s *add_node(list_s **, const char *, int);
list_s *add_to_list(list_s **, const char *, int);
size_t print_list_string(const list_s *);
int delete_node(list_s **, unsigned int);
void free_list(list_s **);
size_t list_length(const list_s *);
char **list_to_str(list_s *);
size_t prints_element(const list_s *);
list_s *start_node(list_s *, char *, char c);
ssize_t node_index(list_s *, list_s *);

/* variables functions */
int is_Chain(cmd_d *, char *buff, size_t *ptr);
void chain_check(cmd_d *, char *, size_t *, size_t, size_t);
int replace_alias(cmd_d *);
int var_replace(cmd_d *);


#endif
