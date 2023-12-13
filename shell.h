#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 1024

extern char **environ;

int _strcmp(const char *str1, const char *str2);
int _strncmp(char *str1, char *str2, int n);
size_t _strcspn(const char *str1, const char *str2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);
int _puts(char *str);
int _putchar(char c);

char *_getenv(const char *name);
int execute_command(char *input);

#endif /* SHELL_H */
