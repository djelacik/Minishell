#include "../../includes/minishell.h"

void	create_pipes(t_cmnds *cmnds)
{
	int		i;

	cmnds->pipes = malloc((cmnds->command_count - 1) * sizeof(int *));
	if (!cmnds->pipes)
	{
		//error_func;
		return ;
	}
	i = 0;
	while (i < cmnds->command_count - 1)
	{
		cmnds->pipes[i] = malloc(sizeof(int) * 2);
		if (!cmnds->pipes[i])
		{
			//error_func;
			return ;
		}
		if (pipe(cmnds->pipes[i] < 0))
		{
			//error_func
			return ;
		}
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
