#include "../../includes/minishell.h"

int	fork_process(int i, int fd_in, int pipefd[2], t_cmnds *cmnds)
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

void	setup_pids(t_cmnds *cmnds)
{
	cmnds->pids = malloc(sizeof(pid_t) * cmnds->command_count);
	if (!cmnds->pids)
	{
		perror(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
}

void	start_process(t_cmnds *cmnds)
{
	int		i;
	int		fd_in;
	int		pipe_fd[2];

	i = 0;
	fd_in = STDIN_FILENO;
	setup_pids(cmnds);
	while (i < cmnds->command_count)
	{
		setup_pipes(i, cmnds->command_count, pipe_fd);
		if (fork_process(i, fd_in, pipe_fd, cmnds) == -1)
		{
			perror(FORK_ERR);
			exit(EXIT_FAILURE);
		}
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (i < cmnds->command_count - 1)
			fd_in = pipe_fd[0];
		i++;
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	wait_for_children(cmnds);
}

void	child_process(int i, int fd_in, int pipe_fd[2], t_cmnds *cmnds)
{
	if (fd_in != STDIN_FILENO) //if fd_in already reading from pipe
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror(DUP2_ERR);
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
	if (pipe_fd[1] != -1) // if this is not the last child process
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror(DUP2_ERR);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
	handle_redirections(&cmnds->data[i]);
	execute_command(cmnds->data[i], cmnds->env_cpy);
	perror(EXEC_ERR);
	exit(EXIT_FAILURE);
}

void	handle_redirection(t_data *cmnd_data)
{
	int		i;
	int		fd;

	i = 0;
	while (i < cmnd_data->redir_count)
	{
		if (cmnd_data->redirs[i].type == REDIRECT_INPUT)// this part is for infile
		{
			handle_input(cmnd_data->redirs[i].file);
		}
		else if (cmnd_data->redirs[i].type == REDIRECT_OUTPUT)// this is for outfile
		{
			handle_output(cmnd_data->redirs[i].file);
		}
		else if (cmnd_data->redirs[i].type == REDIRECT_HEREDOC)
		{
			handle_heredoc(cmnd_data->redirs[i].file);
		}
		i++;
	}
}

static void	handle_input(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(OPEN_ERR);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(DUP2_ERR);
		exit(EXIT_FAILURE);
	}
	close(fd);	
}

static void handle_output(char *filename)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); //flags for appending
	if (fd == -1)
	{
		perror(OPEN_ERR);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(DUP2_ERR);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	int		*line;

	if (pipe(pipe_fd) == -1)
	{
		perror(PIPE_ERR);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, delimiter) == 0)//not sure about '\n'
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror(DUP2_ERR);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
}

void	wait_for_children(t_cmnds *cmnds)
{
	int		i;
	int		status;

	i = 0;
	while (i < cmnds->command_count)
	{
		waitpid(cmnds->pids[i], &status, 0);
		i++;
	}
	free(cmnds->pids);
}
