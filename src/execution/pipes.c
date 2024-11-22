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
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
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

void	close_unused_pipes(int current, t_cmnds *cmnds)
{
	int		i;

	i = 0;
	while (i < cmnds->pipe_count)
	{
		if (i != current)
		{
			close(cmnds->pipes[i][1]);
		}
		if (i != current - 1)
		{
			close(cmnds->pipes[i][0]);
		}
	}
}
