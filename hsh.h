#ifndef HSH_H
#define HSH_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

char **split(char *str, char *delim);
char *which(const char *bin);
void print_err(char *name, char *program, int line);
int prompt(char **input, size_t *len);
void free_array(char **paths);
int exec_builtin(char **args, int *exit);
ssize_t _getline(char **str, size_t *len, FILE *stream);
int execute(char **args, int *status);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

char **parse_args(char **args, int last_status);
char *to_string(int n);

char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

int _puts(char *str);
int _putchar(char ch);

int _strlen(const char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);

#endif /* HSH_H */
