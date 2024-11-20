#include "../../includes/minishell.h"

void    execute_command(t_command *command, t_cmnds *cmnds)
{
    char    *cmd;
    char    **args;
    int     i;

    cmd = command->tokens[0].token_string;
    args = malloc(sizeof(char *) * (command->token_count + 1));
    if (!args)
    {
        perror(MALLOC_ERR);
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (i < command->token_count)
    {
        args[i] = command->tokens[i].token_string;
        i++;
    }
    args[i] = NULL;
    if (execve(cmd, args, cmnds->argv_cpy) == -1)
    {
        perror(EXECVE_ERR);
        exit(EXIT_FAILURE);
    }
}
