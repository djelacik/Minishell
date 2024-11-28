#include "../../includes/minishell.h"

static void	close_unused_fds(void)
{
	int		fd;
	int		open_max;

	fd = 3;
	open_max = 1024;
	while (fd < open_max)
	{
		close(fd);
		fd++;
	}
}

static void	setup_input_output(int fd_in, int pipe_fd[2])
{
	if (fd_in != STDIN_FILENO)
	{
		dbg_print("Redirecting input (fd_in: %d -> STDIN_FILENO)\n", fd_in);
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror(DUP2_ERR);
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
	if (pipe_fd[1] != -1)
	{
		dbg_print("Redirecting output (pipe_fd[1]: %d -> STDOUT_FILENO)\n", pipe_fd[1]);
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
	//dbg_print("Child process %d handling redirections\n", i);
	handle_redirection(&cmnds->data[i]);
	dbg_print("Child process %d executing command: %s\n", i, cmnds->data[i].args[0].token_string);
	close_unused_fds();
	execute_command(&cmnds->data[i], cmnds);
	perror(EXEC_ERR);
	exit(EXIT_FAILURE);
}

void	child_process(int i, int fd_in, int pipe_fd[2], t_cmnds *cmnds)
{
	dbg_print("Child process %d setting up input/output redirections\n", i);
	setup_input_output(fd_in, pipe_fd);
	setup_input_output(fd_in, pipe_fd);
	dbg_print("Child process %d starting command execution\n", i);
	execute_child_command(i, cmnds);
}
