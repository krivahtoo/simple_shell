#ifndef HSH_H
#define HSH_H

extern char **environ;

char **split(char *str, char delim);
char *which(const char *bin);
int _strlen(char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif /* HSH_H */
