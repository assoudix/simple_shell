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
