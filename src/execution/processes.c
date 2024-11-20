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

void	child_first(int i, t_cmnds *cmnds)
{
	//dup2(new_fd, old_fd)
	if (dup2(cmnds->pipes[i][1], STDOUT_FILENO) < 0)
	{
		perror(CHILD_FIRST_ERR);
		exit(EXIT_FAILURE);
	}
	close_pipes();
	execute_command();
	perror(EXEC_ERR);
	exit(EXIT_FAILURE);
}

void	child_middle(int i, t_cmnds *cmnds)
{
	if (dup2(cmnds->pipes[i - 1][0], STDIN_FILENO) < 0)
	{
		perror(CHILD_MID_ERR);
		exit(EXIT_FAILURE);
	}
	if (dup2(cmnds->pipes[i][1], STDOUT_FILENO) < 0)
	{
		perror(CHILD_MID_ERR);
		exit(EXIT_FAILURE);
	}
	close_pipes();
	exexute_command();
	perror(EXEC_ERR);
	exit(EXIT_FAILURE);
}

void	child_last(int i, t_cmnds *cmnds)
{
	if (dup2(cmnds->pipes[i - 1][0], STDIN_FILENO) < 0)
	{
		perror(CHILD_LAST_ERR);
		exit(EXIT_FAILURE);
	}
	close_pipes();
	execute_command();
	perror(EXEC_ERR);
	exit(EXIT_FAILURE);
}
