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

	/*commands = tokenize_input(cmd);

	free(cmd);

	cmd = commands[0];
	free(commands);*/

	return (cmd);
}

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

