#include "shell.h"

/**
 * handle_exit - Handle the "exit" command
 * @command: command to be parsed
 *
 * Return: void
 */
void handle_exit(char *command)
{
	int status;
	char *tokenized;

	tokenized = strtok(command, " ");

	if (_strcmp(tokenized, "exit") == 0)
	{
		tokenized = strtok(NULL, " ");
		if (tokenized != NULL)
		{
			status = atoi(tokenized);
			exit(status);
		}
		else
			exit(0);
	}
}
