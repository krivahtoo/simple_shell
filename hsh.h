#ifndef HSH_H
#define HSH_H

extern char **environ;

char **split(char *str, char delim);
char *which(const char *bin);

#endif /* HSH_H */
