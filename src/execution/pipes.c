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
