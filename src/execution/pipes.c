#include "../../includes/minishell.h"

void	setup_pipes(int i, int command_count, int pipefd[2])
{
	if (i < command_count - 1)
	{
		if (pipe(pipefd) == -1)
		{
			perror(PIPE_ERR);
			exit(EXIT_FAILURE);
		}
		dbg_print("Created pipe (pipefd[0]: %d, pipefd[1]: %d)\n", pipefd[0], pipefd[1]);
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		dbg_print("No pipe created for last command, set pipefd to [-1, -1]\n");
	}
}

void	close_all_pipes(t_cmnds *cmnds)
{
	int		i;

	i = 0;
	while (i < cmnds->pipe_count)
	{
		close(cmnds->pipes[i][0]);
		close(cmnds->pipes[i][1]);
		free(cmnds->pipes[i]);
		i++;
	}
	free(cmnds->pipes);
}
