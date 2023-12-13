#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_TOKENS_NUM 64
extern char **environ;

/**
 * struct CmdInfo - Command information
 * @cmd: Original command
 * @args: Tokenized arguments
 * @full_path: Full path to the executable
 * @prog_name: Name of the program
 */
typedef struct CmdInfo
{
	char *cmd;
	char **args;
	char *full_path;
	const char *prog_name;
} CmdInfo;

void _putchar(char c);
void _puts(const char *s);
size_t _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, int c);

void exec_cmd_from_path(CmdInfo *info, int *status);
void exec_cmd(char *cmd, int *status, const char *prog_name);
char *find_exec_path(char *cmd, char *search_path);
char **tokenize_input(const char *input);
void free_str_array(char **array);
int handle_exit_cmd(char *cmd, int *status);
char *read_input(void);
int handle_env_cmd(char *cmd);
void print_exec_error(char *cmd, const char *prog_name);
char *get_env_variable(const char *name);

#endif /* SHELL_H */

