#include "ss.h"

/**
 * exec_cmd_from_path - Execute command from path
 * @info: Command information
 * @status: Status of the command
 */
void exec_cmd_from_path(CmdInfo *info, int *status)
{
	(void)status;

	if (info->full_path != NULL && access(info->full_path, F_OK) == 0)
	{
		if (access(info->full_path, X_OK) == -1)
		{
			print_exec_error(info->cmd, info->prog_name);
			free_str_array(info->args);
			free(info->cmd);
			free(info->full_path);
			exit(127);
		}
		if (execve(info->full_path, info->args, environ) != -1)
		{
			free_str_array(info->args);
			free(info->full_path);
			exit(EXIT_SUCCESS);
		}
	}
	if (_strchr(info->args[0], '/') == NULL)
	{
		print_exec_error(info->cmd, info->prog_name);
		free_str_array(info->args);
		free(info->cmd);
		free(info->full_path);
		exit(127);
	}
	if (execve(info->args[0], info->args, environ) == -1)
	{
		print_exec_error(info->cmd, info->prog_name);
		free_str_array(info->args);
		free(info->cmd);
		free(info->full_path);
		exit(127);
	}
}

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
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * tokenize_input - Tokenize input
 * @input: Input to tokenize
 * Return: Tokenized input
 */
char **tokenize_input(const char *input)
{
	char *str;
	int count = 0;
	char **result;
	char *token;

	str = _strdup(input);
	result = malloc(MAX_TOKENS_NUM * sizeof(*result));

	token = strtok(str, " \n\t");

	while (token != NULL && count < MAX_TOKENS_NUM - 1)
	{
		if (_strlen(token) > 0)
		{
			result[count] = _strdup(token);
			count++;
		}
		token = strtok(NULL, " \n\t");
	}

	result[count] = NULL;
	free(str);

	return (result);
}

/**
 * free_str_array - Free string array
 * @array: Array to free
 */
void free_str_array(char **array)
{
	int i;

	for (i = 0; array[i]; ++i)
		free(array[i]);
	free(array);
}
