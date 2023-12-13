#include "ss.h"

/**
 * handle_exit_cmd - Handle exit command
 * @cmd: Command to handle
 * @status: Status of the command
 * Return: 1 if command is not "exit", otherwise exit
 */
int handle_exit_cmd(char *cmd, int *status)
{
        if (_strcmp(cmd, "exit") == 0)
        {
                if (*status != 0)
                {
                        free(cmd);
                        exit(2);
                }
                else
                {
                        free(cmd);
                        exit(0);
                }
        }
        return (1);
}

/**
 * read_input - Read input
 * Return: Input read
 */
char *read_input(void)
{
        char *cmd = NULL;
        size_t buffer_size = 0;
        ssize_t line_length;

        line_length = getline(&cmd, &buffer_size, stdin);
        if (line_length == -1)
        {
                free(cmd);
                if (isatty(STDIN_FILENO))
                        putchar('\n');
                return (NULL);
        }
        if (cmd[line_length - 1] == '\n')
                cmd[line_length - 1] = '\0';

        return (cmd);
}
