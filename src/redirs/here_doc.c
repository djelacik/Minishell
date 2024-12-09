#include "../../includes/minishell.h"

static void	read_heredoc_input(int pipe_fd[2], char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
}

static void	setup_heredoc_pipe(int pipe_fd[2])
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror(DUP2_ERR);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
}

void	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror(PIPE_ERR);
		exit(EXIT_FAILURE);
	}
	read_heredoc_input(pipe_fd, delimiter);
	setup_heredoc_pipe(pipe_fd);
}
