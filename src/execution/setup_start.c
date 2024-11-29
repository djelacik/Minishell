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
	dbg_print("Forking process %d (fd_in: %d, pipe_out: %d)\n", i, fd_in, pipefd[1]);
	cmnds->pids[i] = fork();
	if (cmnds->pids[i] < 0)
	{
		perror(FORK_ERR);
		return (-1);
	}
	if (cmnds->pids[i] == 0)
	{
		dbg_print("Child process %d created (PID: %d)\n", i, getpid());
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
	{
		dbg_print("Parent closing fd_in: %d\n", fd_in);
		//close(fd_in);
	}
	if (pipe_fd[1] != -1)
	{
		dbg_print("Parent closing pipe_fd[1]: %d\n", pipe_fd[1]);
		close(pipe_fd[1]);
	}
	if (i < cmnds->command_count - 1)
		return (pipe_fd[0]);
	else
	{
		if (fd_in != STDIN_FILENO)
		{
			dbg_print("Parent closing fd_in: %d\n", fd_in);
			close(fd_in);
		}
		if (pipe_fd[0] != -1)
		{
			dbg_print("Parent closing pipe_fd[0]: %d\n", pipe_fd[0]);
			close(pipe_fd[0]);
		}
		return (STDIN_FILENO);
	}
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

static void	execute_in_parent(t_data *data, t_cmnds *cmnds)
{
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	handle_redirections(data);
	execute_builtin(data, cmnds);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}


static int	should_execute_in_parent(t_data *data, int command_count)
{
	if (command_count == 1 && is_builtin(data->args[0].token_string))
		return 1;
	return 0;
}

static void	set_is_in_pipe(t_cmnds *cmnds)
{
	int		i;

	i = 0;
	while (i < cmnds->command_count)
	{
		if (cmnds->command_count > 1)
			cmnds->data[i].is_in_pipe = 1;
		else
			cmnds->data[i].is_in_pipe = 0;
		i++;
	}
}

void	start_process(t_cmnds *cmnds)
{
	int		i;
	int		fd_in;

	fd_in = STDIN_FILENO;
	setup_pids(cmnds);
	set_is_in_pipe(cmnds);
	i = 0;
	while (i < cmnds->command_count)
	{
		if (should_execute_in_parent(&cmnds->data[i], cmnds->command_count))
		{
			dbg_print("We are executing in parent\n");
			execute_in_parent(&cmnds->data[i], cmnds);
		}
		else
		{
			dbg_print("We are executing in child\n");
			fd_in = execute_process(i, fd_in, cmnds);
		}
		i++;
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	wait_for_children(cmnds);
}

