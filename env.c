#include "ss.h"

/**
 * handle_env_cmd - Handle env command
 * @cmd: Command to handle
 * Return: 0 if command is "env", 1 otherwise
 */
int handle_env_cmd(char *cmd)
{
        int i = 0;

        if (_strcmp(cmd, "env") == 0)
        {
                while (environ[i])
                        _puts(environ[i++]);
                free(cmd);
                return (0);
        }
        return (1);
}

/**
 * get_env_variable - Get environment variable
 * @name: Name of the variable
 * Return: Value of the variable
 */
char *get_env_variable(const char *name)
{
        int i = 0;
        size_t length = _strlen(name);

        while (environ[i])
        {
                if (_strncmp(name, environ[i], length) == 0 &&
                                environ[i][length] == '=')
                        return (&environ[i][length + 1]);
                i++;
        }
        return (NULL);
}
