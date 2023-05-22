#ifndef HSH_H
#define HSH_H

extern char **environ;

char **split(char *str, char *delim);
char *which(const char *bin);
void print_err(char *name, char *program, int line);

#endif /* HSH_H */
