#include "ss.h"

/**
 * main - Main function
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Exit status
 */
int main(int argc, char *argv[])
{
	char *user_input = NULL;
	int exit_status = 0;
	const char *prog_name = argv[0];

	(void)argc;

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			user_input = read_input();
			if (user_input == NULL)
				break;
			exec_cmd(user_input, &exit_status, prog_name);
		}
	}
	else
	{
		while ((user_input = read_input()) != NULL)
		{
			exec_cmd(user_input, &exit_status, prog_name);
		}
	}

	return (exit_status);
}
