#include "ss.h"

/**
 * exec_cmd - Execute command
 * @cmd: Command to execute
 * @status: Status of the command
 * @prog_name: Name of the program
 */
void exec_cmd(char *cmd, int *status, const char *prog_name)
{
        pid_t pid;
        char **args = NULL;
        char *full_path = NULL;
        CmdInfo cmd_info;

        pid = fork();
        if (pid == 0)
        {
                args = tokenize_input(cmd);
                if (args == NULL || args[0] == NULL)
                {
                        free_str_array(args);
                        free(cmd);
                        return;
                }
                full_path = find_exec_path(args[0], get_env_variable("PATH"));

                cmd_info.cmd = cmd;
                cmd_info.args = args;
                cmd_info.full_path = full_path;
                cmd_info.prog_name = prog_name;

                exec_cmd_from_path(&cmd_info, status);
        }
        else
        {
                wait(status);
                if (WIFEXITED(*status))
                        *status = WEXITSTATUS(*status);
                else
                        *status = 127;
        }
        free(cmd);
}

/**
 * find_exec_path - Find executable path
 * @cmd: Command to execute
 * @search_path: Search path
 * Return: Full path of the command
 */
char *find_exec_path(char *cmd, char *search_path)
{
        char *path_copy = NULL, *dir = NULL, *full_path = NULL;

        if (search_path == NULL || cmd == NULL)
                return (NULL);

        path_copy = _strdup(search_path);
        dir = strtok(path_copy, ":");

        while (dir)
        {
                full_path = malloc(_strlen(dir) + 1 + _strlen(cmd) + 1);

                if (full_path == NULL)
                {
                        free(path_copy);
                        return (NULL);
                }

                _strcpy(full_path, dir);
                _strcat(full_path, "/");
                _strcat(full_path, cmd);

                if (access(full_path, X_OK) == 0)
                {
                        free(path_copy);
                        return full_path;
                }
                free(full_path);
                dir = strtok(NULL, ":");
        }

        free(path_copy);
        return (NULL);
}

/**
 * print_exec_error - Print execution error
 * @cmd: Command that caused the error
 * @prog_name: Name of the program
 */
void print_exec_error(char *cmd, const char *prog_name)
{
        if (isatty(STDIN_FILENO))
        {
                write(STDOUT_FILENO, cmd, strlen(cmd));
                write(STDOUT_FILENO, ": command not found\n", 20);
        }
        else
        {
                write(STDERR_FILENO, prog_name, _strlen(prog_name));
                write(STDERR_FILENO, ": 1: ", 5);
                write(STDERR_FILENO, cmd, _strlen(cmd));
                write(STDERR_FILENO, ": not found\n", 12);
        }
}
