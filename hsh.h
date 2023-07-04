#ifndef HSH_H
#define HSH_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define OP_NONE	0
#define OP_OR	1
#define OP_AND	2

extern char **environ;

/**
 * struct buf - string buffer
 *
 * @ptr: string pointer
 * @len: size of buffer
 */
typedef struct buf
{
	char *ptr;
	size_t len;
} buf_t;

/**
 * struct node - linked list node
 *
 * @key: key of the node
 * @value: node value
 * @next: next node
 */
typedef struct node
{
	char *key;
	char *value;
	struct node *next;
} node_t;

/**
 * struct command - commands to execute in a line
 *
 * @name: command name
 * @args: command arguments
 * @op: operator
 * @next: next command
 */
typedef struct command
{
	char *name;
	char **args;
	char op;
	struct command *next;
} command_t;

/**
 * struct context - context data for our shell
 *
 * @name: name of program according to argv[0]
 * @line: current line number of piped content or file
 * @cmd: parsed list of commands
 * @env: head of the env variables linked list
 * @aliases: head of the alias linkeed list
 * @buf: buffer to store input
 * @status: exit status of the child process
 * @isatty: if current file descriptor is a tty
 */
typedef struct context
{
	char *name;
	size_t line;
	command_t *cmd;
	node_t *env;
	node_t *aliases;
	buf_t buf;
	int status;
	u_int8_t isatty;
} context_t;

/**
 * struct builtin - builtin commands.
 *
 * @name: command name
 * @f: function pointer
 */
typedef struct builtin
{
	char *name;
	int (*f)(context_t *ctx);
} builtin_t;

/* builtins */
int builtin_env(context_t *ctx);
int builtin_exit(context_t *ctx);
int builtin_setenv(context_t *ctx);
int builtin_unsetenv(context_t *ctx);
int builtin_cd(context_t *ctx);
int builtin_alias(context_t *ctx);

char **split(char *str, char *delim);
char *which(const char *bin, context_t *ctx);
void print_err(context_t *ctx, char *err);
int prompt(context_t *ctx, FILE *stream);

void free_array(char **arr);
void free_buf(buf_t *buf);
void free_ctx(context_t *ctx);

int exec_builtin(context_t *ctx);
ssize_t _getline(char **str, size_t *len, FILE *stream);
int execute(context_t *ctx);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

void parse_commands(context_t *ctx, char *input);
void parse_args(context_t *ctx);
char *to_string(int n);

void allocate_env(context_t *ctx);
char *_getenv(const char *name, context_t *ctx);
int _setenv(
	const char *name,
	const char *value,
	int overwrite,
	context_t *ctx
);
int _unsetenv(const char *name, context_t *ctx);

/* linked list */
void free_list(node_t **head);
size_t print_list(const node_t *h);
char **to_array(node_t *h);
node_t *get_node(node_t *head, const char *key);
size_t pop_node(node_t **head, const char *key);
node_t *add_node_end(node_t **head, const char *key, const char *value);

/* command list */
void free_commands(command_t **head);
void add_command(command_t **head, const char *args, char op);
command_t *next_command(command_t **head);

int _puts(char *str);
int _putchar(char ch);
int puts_err(char *str);
int putchar_err(char ch);

int _atoi(char *str);

int _strcmp(const char *s1, const char *s2);
int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);

#endif /* HSH_H */
