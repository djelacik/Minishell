#include "../../includes/minishell.h"

static void	setup_pids(t_cmnds *cmnds)
{
	cmnds->pids = malloc(sizeof(pid_t) * cmnds->command_count);
	if (!cmnds->pids)
	{
		perror(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
}

static int	fork_process(int i, int fd_in, int pipefd[2], t_cmnds *cmnds)
{
	cmnds->pids[i] = fork();
	if (cmnds->pids[i] < 0)
	{
		perror(FORK_ERR);
		return (-1);
	}
	if (cmnds->pids[i] == 0)
	{
		child_process(i, fd_in, pipefd, cmnds);
	}
	return (0);
}

static int	execute_process(int i, int fd_in, t_cmnds *cmnds)
{
	int		pipe_fd[2];

	setup_pipes(i, cmnds->command_count, pipe_fd);
	if (fork_process(i, fd_in, pipe_fd, cmnds) == -1)
	{
		perror(FORK_ERR);
		exit(EXIT_FAILURE);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (i < cmnds->command_count - 1)
		return (pipe_fd[0]);
	return (STDIN_FILENO);

}

static void	wait_for_children(t_cmnds *cmnds)
{
	int		i;
	int		status;

	i = 0;
	while (i < cmnds->command_count)
	{
		waitpid(cmnds->pids[i], &status, 0);
		i++;
	}
	//free(cmnds->pids);
}

void	start_process(t_cmnds *cmnds)
{
	int		i;
	int		fd_in;

	fd_in = STDIN_FILENO;
	setup_pids(cmnds);
	i = 0;
	while (i < cmnds->command_count)
	{
		fd_in = execute_process(i, fd_in, cmnds);
		i++;
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	wait_for_children(cmnds);
}
