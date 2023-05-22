#ifndef HSH_H
#define HSH_H

#include <stddef.h>
#include <stdlib.h>

extern char **environ;

char **split(char *str, char *delim);
char *which(const char *bin);
void print_err(char *name, char *program, int line);

int _strlen(const char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(const char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif /* HSH_H */
