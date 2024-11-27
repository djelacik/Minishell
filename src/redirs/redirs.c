#include "../../includes/minishell.h"

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


void	handle_redirection(t_data *cmnd_data)
{
	int		i;

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
