#ifndef S_SHELL_H
#define S_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Prototypes of copy_concat.c */
char *_copyString(char *, char *, int);
char *_concatenateStrings(char *, char *, int);
char *_findCharacter(char *, char);

/* Prototypes of stringToInteger.c */
int string_to_integer(char *);
int is_interactive(info_t *);
int is_delimiter(char, char *);
int checkAlpha(int);

/* Prototypes of errors.c */
int str_to_int(char *);
void print_custom_error(info_t *, char *);
int print_decimal(int, int);
char *convert_to_string(long int, int, int);
void remove_first_comment(char *);

/* Prototypes of exit_help_cd.c */
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);

/* Prototypes of history_alias.c */
int display_history(info_t *);
int manage_alias(info_t *);

/*Prototypes of getline.c */
ssize_t obtain_input(info_t *);
int _getline_custom(info_t *, char **, size_t *);
void interruptHandler(int);
/* Prototypes of sh_loop.c */
int my_shell(info_t *, char **);
int find_shell_builtin(info_t *);
void fork_shell_command(info_t *);
void find_shell_command(info_t *);

/* Prototypes of parser.c */
int is_executable(info_t *, char *);
char *copy_chars(char *, int, int);
char *search_in_path(info_t *, char *, char *);

/* Prototypes of print_char.c */
void cust_puts(char *);
int cust_putchar(char);
int put_to_fd(char char_input, int file_descriptor);
int cust_puts_to_fd(char *str_input, int file_descriptor);

/* Prototypes of string.c */
int cust_strlen(char *);
int cust_strcmp(char *, char *);
char *cust_starts_with(const char *, const char *);
char *cust_strcat(char *, char *);

/* Prototypes of string1.c */
char *copyString(char *, char *);
char *duplicateString(const char *);
void printString(char *);
int writeCharacter(char);

/* Prototypes of tokenizer.c */
char **splitString(char *, char *);
char **splitString2(char *, char);

/* Prototypes of realloc.c */
char *cust_memset(char *, char, unsigned int);
void cust_free(char **);
void *cust_realloc(void *, unsigned int, unsigned int);

/*Prototypes of memory.c */
int myfree(void **);

/* Prototypes of getinfo.c */
void initialize_data(info_t *);
void populate_data(info_t *, char **);
void release_data(info_t *, int);

/* Prototypes of environ_var.c */
char *get_environment_variable(info_t *, const char *);
int print_environment(info_t *);
int set_environment_variable(info_t *);
int unset_environment_variable(info_t *);
int populate_environment_list(info_t *);

/* Prototypes of getenv.c */
char **obtain_environment(info_t *);
int remove_environment_variable(info_t *, char *);
int update_environment_variable(info_t *, char *, char *);

/* Prototypes of history.c */
char *fetch_history_file(info_t *information);
int save_history(info_t *information);
int load_history(info_t *information);
int append_to_history_list(info_t *information, char *buffer, int line_count);
int renumber_history_list(info_t *information);

/* Prototypes of lists.c */
list_t *prepend_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t print_list_strings(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void clear_list(list_t **);

/* Prototypes of lists1.c */
size_t cust_list_length(const list_t *);
char **cust_list_to_strings(list_t *);
size_t cust_print_list(const list_t *);
list_t *cust_node_starts_with(list_t *, char *, char);
ssize_t cust_get_node_index(list_t *, list_t *);

/* Prototypes of vars.c */
int is_chain_delimiter(info_t *, char *, size_t *);
void checkDelimiter(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);

#endif
