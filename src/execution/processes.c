#include "../../includes/minishell.h"

void	start_process(t_cmnds *cmnds, char **argv)
{
	int		i;

	i = 0;
	cmnds->pid = malloc(sizeof(pid_t) * cmnds->command_count); //process id
	while (i < cmnds->command_count)
	{
		cmnds->pid[i] = fork(); //start of child processes
		if (cmnds->pid[i] < 0)
		{
			//error func;
			return ;
		}
		if (cmnds->pid[i] == 0) //if is a child process
		{
			//close_unused_pipes();
			if (i == 0)
				child_first();
			else if (i == cmnds->command_count - 1)
				child_last();
			else
				child_middle();
		}
		i++;
	}
	//close_all_pipes();
	//exit(wait_children());

}

void    child_read(int i, t_cmnds *cmnds, char **argv);
{
    
}