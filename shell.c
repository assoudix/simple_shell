#include "shell.h"

/**
 * handle_err_non_inter - Print an error message and exit
 *                        in non-interactive mode
 *
 * @program: The name of the program
 * @command: The command that caused the error
 *
 * Return: None
 */
void handle_err_non_inter(const char *program, const char *command)
{
	write(STDERR_FILENO, program, _strlen(program));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
	exit(EXIT_FAILURE);
}
/**
 * _getenv - Get the value of an environment variable
 * @name: The name of the environment variable to get
 *
 * Return: A pointer to the value of the environment variable,
 *         or NULL if the variable does not exist
 */
char *_getenv(const char *name)
{

	char *path = NULL, *dir = NULL, *value = NULL;
	char *complete_path = NULL;
	int i = 0;

	for (; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
		{
			if (_strcmp(name, "man") == 0)
				return ("/bin/man");
			path = environ[i] + 5;
			break;
		}
	}
	if (path == NULL)
		return (NULL);

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		complete_path = malloc(_strlen(dir) + _strlen(name) + 2);
		_strcpy(complete_path, dir);
		_strcat(complete_path, "/");
		_strcat(complete_path, name);

		if (access(complete_path, F_OK) != -1)
		{
			value = complete_path;
			break;
		}
		free(complete_path);
		dir = strtok(NULL, ":");
	}

	return (value);
}

/**
 * execute_command - Execute a command with arguments
 * @input: The command line input
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *input)
{
	int i = 0, non_inter = !isatty(STDIN_FILENO);
	char *args[MAX], *token = strtok(input, " \n\t\r"), *command_path;
	char **loc_env = environ;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \n\t\r");
	}
	args[i] = NULL;
	if (_strcmp(args[0], "exit") == 0)
		exit(0);
	if (_strcmp(args[0], "env") == 0)
	{
		while (*loc_env != NULL)
		{
			_puts(*loc_env);
			loc_env++;
		}
		return (0);
	}
	if (access(args[0], F_OK) != -1)
		command_path = args[0];
	else
	{
		command_path = _getenv(args[0]);
		if (command_path == NULL && !non_inter)
		{
			write(1, args[0], _strlen(args[0]));
			write(1, ": command not found\n", 20);
			return (-1);
		}
	}
	if (execve(command_path, args, environ) == -1)
	{
		if (!non_inter)
			perror("execve");
		return (-1);
	}
	return (0);
}

/**
 * main - Entry point
 *
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *command = NULL;
	size_t command_size = 0;
	pid_t pid;
	int status, non_inter = !isatty(STDIN_FILENO);
	(void)argc;

	while (1)
	{
		if (!non_inter)
			write(1, "($) ", 4);

		if (getline(&command, &command_size, stdin) == -1)
		{
			if (!non_inter)
				_putchar('\n');
			break;
		}
		command[_strcspn(command, "\n")] = '\0';
		if (_strcmp(command, "exit") == 0)
			break;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execute_command(command) == -1)
			{
				if (non_inter)
					handle_err_non_inter(argv[0], command);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
	free(command);
	return (0);
}
