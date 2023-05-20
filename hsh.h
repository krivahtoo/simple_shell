#ifndef HSH_H
#define HSH_H

extern char **environ;

char **split(char *str, char delim);
char *which(const char *bin);
int _setenv(const char *name, const char *value, int overwrite);

#endif /* HSH_H */
