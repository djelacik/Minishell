#include "../../includes/minishell.h"

static void	close_unused_fds(void)
{
	int		fd;

	fd = 3;
	while (fd < OPEN_MAX)
	{
		close(fd);
		fd++;
	}
}

static void	setup_input_output(int fd_in, int pipe_fd[2])
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror(DUP2_ERR);
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
	if (pipe_fd[1] != -1)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror(DUP2_ERR);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
	else
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
	}
}

static void	execute_child_command(int i, t_cmnds *cmnds)
{
	handle_redirection(&cmnds->data[i]);
	close_unused_fds();
	execute_command(&cmnds->data[i], cmnds);
	perror(EXEC_ERR);
	exit(EXIT_FAILURE);
}

void	child_process(int i, int fd_in, int pipe_fd[2], t_cmnds *cmnds)
{
	setup_input_output(fd_in, pipe_fd);
	execute_child_command(i, cmnds);
}
