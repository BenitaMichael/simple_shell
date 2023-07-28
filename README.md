# simple_shell
Simple shell project using C programming language

# Table of Content
 <ol>
  <li>What is shell</li>
  <li>List of allowed functions and system calls for this project</li>
  <li>Authors</li>
 </ol>
<hr/>

## What is shell?
- Shell is an environment in which we can run our commands, programs, and shell scripts.

- Simply put, the shell is a program that takes commands from the keyboard and gives them to the operating system to perform.

<hr/>

## List of allowed functions and system calls for this project

- Functions allowed are:
<ul>
 <li>access (man 2 access)</li>
 <li>chdir (man 2 chdir)</li>
 <li>close (man 2 close)</li>
 <li>closedir (man 3 closedir)</li>
 <li>execve (man 2 execve)</li>
 <li>exit (man 3 exit)</li>
 <li>_exit (man 2 _exit)</li>
 <li>fflush (man 3 fflush)</li>
 <li>fork (man 2 fork)</li>
 <li>free (man 3 free)</li>
 <li>getcwd (man 3 getcwd)</li>
 <li>getline (man 3 getline)</li>
 <li>getpid (man 2 getpid)</li>
 <li>isatty (man 3 isatty)</li>
 <li>kill (man 2 kill)</li>
 <li>malloc (man 3 malloc)</li>
 <li>open (man 2 open)</li>
 <li>opendir (man 3 opendir)</li>
 <li>perror (man 3 perror)</li>
 <li>read (man 2 read)</li>
 <li>readdir (man 3 readdir)</li>
 <li>signal (man 2 signal)</li>
 <li>stat (__xstat) (man 2 stat)</li>
 <li>lstat (__lxstat) (man 2 lstat)</li>
 <li>fstat (__fxstat) (man 2 fstat)</li>
 <li>strtok (man 3 strtok)</li>
 <li>wait (man 2 wait)</li>
 <li>waitpid (man 2 waitpid)</li>
 <li>wait3 (man 2 wait3)</li>
 <li>wait4 (man 2 wait4)</li>
 <li>write (man 2 write)</li>
</ul>
<hr/>

## List of function and system calls use
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
        struct list_str *nxt;
} list_s;
/**
 * struct passdat - linked list
 * @arg: pointer to strings with arguments
 * @argv: pointer to an array of strings
 * @path: string path
 * @argc: argument count (command-line arguments)
 * @len_count: characters count in a string.
 * @error_num: error code
 * @line_count_flag: flag to count line of string inputs
 * @file_name: pointer to program file
 * @read_file: file descriptor used for reading inputs
 * @env: linked list of environ variables
 * @environ: array of environ variables
 * @env_changed: checks for if environment has changed
 * @history: pointer to past entry
 * @history_count: memory for prev command entered
 * @stats: result from prev command
 * @alias: command aliases
 * @cmd_buf: pointer address to command buffer
 * @cmd_buff_type: command buffer (CMD_type: || 0r &&, )
 */d
typedef struct cmddata
{
 -       char *arg;
 -      char **argv;
 -       char *path;
 -       int argc;
 -       unsigned int len_count;
 -       int error_num;
 -       int line_count_flag;
 -       char *file_name;
 -       list_s *env;
 -       list_s *history;
 -       list_s *alias;
 -       char **environ;
 -       int env_changed;
 -       int stats;
 -       char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
 -       int cmd_buff_type; /* CMD_type ||, &&, ; */
 -       int read_file;
 -       int history_count;
} cmd_d;

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


/* _string function(s) */
- int _putchar(char);
- void append_S(char *str); /*appends strings from character*/
- size_t string_length(char *str);
- int my_str_comp(const char *, const char *);
- char *my_str_copy(char *str, char *src);
- char *str_duplicate(const char *str);
- char *_check(const char *haystack, const char *needle);


/*fork function(s)*/
- void fork_c(cmd_d *cmd_dat);

/* simple shell loop functions */
- int shell(cmd_d *cmd_dat, char **av);
- int find_builtIn(cmd_d *cmd_dat);
- void path_cmd(cmd_d *cmd_dat);

/* parse functions */
- int if_exec_cmd(cmd_d *cmd_dat, char *path);
- char *char_dup(char *, int, int);
- char *find_full_path(cmd_d *dat, char *path_str, char *cmd);


/* error functions */
- void append_err_s(char *);
- int err_putchar(char);
- int fd_putc(char c, int fd);
- int fd_puts(char *str, int fd);
- int err_atoi(char *s);
- void print_err(cmd_d *, char *);
- int print_decimal(int, int);
- char *convert_num(long int, int, int);
- void rm_comments(char *);

/* interactive shell function(s) */
- int interactive_shell(cmd_d *);

/* _atoi functions */
- int _atoi(char *);
- int is_alpha(int c);
- int is_delimeter(char, char *);

/* alias function(s) */
- int _set_alias(cmd_d *cmd_dat, char *str);
- int _unset_alias(cmd_d *cmd_dat, char *str);
- int a_print(list_s *_node);
- int alias_cmd(cmd_d *cmd_dat);

/* token function(s) */
- char **token(char *str, char *delim);

/* built in command function */
- int exit_cmd(cmd_d *cmd_dat);
- int history_cmd(cmd_d *cmd_dat);
- int help_cmd(cmd_d *cmd_dat);
- int cd_cmd(cmd_d *cmd_dat);

/* memory allocation functions (realloc) */
- char *memory_set(char *, char, unsigned int);
- void str_free(char **);
- void *my_realloc(void *, unsigned int, unsigned int);

/* environ functions */
- char **get_env(cmd_d *cmd_dat);
- int set_env(cmd_d *, char *, char *); /* still confusing */
- int unset_env(cmd_d *, char *);

/* environment functions */
- char *_get_env(cmd_d *, const char *);
- int my_env(cmd_d *cmd_dat);
- int set_environ(cmd_d *cmd_dat);
- int unset_environ(cmd_d *cmd_dat);
- int populate_env(cmd_d *cmd_dat);

/* history functions */
- char *history_file(cmd_d *cmd_dat);
- int rd_history(cmd_d *cmd_dat);
- int write_history(cmd_d *cmd_dat);
- int build_history(cmd_d *cmd_dat, char *buf, int line_count);
- int renumber_history(cmd_d *cmd_dat);


/* getline functions (my getline functions) */
- int my_getline(cmd_d *cmd_dat, char **ptr, size_t *len);
- ssize_t input_buffer(cmd_d *dat, char **buf, size_t *_len);
- ssize_t read_buf(cmd_d *cmd_dat, char *buf, size_t *i);
- ssize_t _input(cmd_d *cmd_dat);
- void signalHandler(int);

/* command data functions */
- void set_cmd(cmd_d *cmd_dat, char **av);
- void clear_cmd(cmd_d *cmd_dat);
- void free_cmd(cmd_d *cmd_dat, int t);

/* linked list functions */
- list_s *add_node(list_s **, const char *, int);
- list_s *add_to_list(list_s **, const char *, int);
- size_t print_list_string(const list_s *);
- int delete_node(list_s **, unsigned int);
- void free_list(list_s **);

/* more linked lists functions */
- size_t list_length(const list_s *);
- char **list_to_str(list_s *);
- size_t print_list(const list_s *h);
- list_s *start_node(list_s *, char *, char);
- ssize_t node_index(list_s *, list_s *);

/* variable functions */
- int is_Chain(cmd_d *cmd_dat, char *buff, size_t *ptr);
- void chain_check(cmd_d *, char *, size_t *, size_t, size_t);
- int replace_alias(cmd_d *cmd_dat);
- int var_replace(cmd_d *cmd_dat);
- int replace_str(char **o, char *n);

<hr>

## Authors
<b><a href= "https://github.com/kabasilim">Abasilim Kosisochukwu Obaejeogu> </a> </b>
<br/>
<b><a href= "https://github.com/BenitaMichael">Benita Koliseyenum Enubiaka> </a> </b>
