#include "../../includes/minishell.h"

static void	handle_input(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(OPEN_ERR);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror(DUP2_ERR);
		return ;
	}
	close(fd);	
}

static void handle_output(char *filename, int flags)
{
	int		fd;

	fd = open(filename, flags, 0644); //flags for appending
	if (fd == -1)
	{
		perror(OPEN_ERR);
		return ; // free?
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(DUP2_ERR);
		return ; // free?
	}
	close(fd);
}

void	handle_redirections_parent(t_data *cmnd_data, t_cmnds *cmnds)
{
	int		i;

	dbg_print("Handling redirections (redir_count: %d)\n", cmnd_data->redir_count);
	i = 0;
	while (i < cmnd_data->redir_count)
	{
		if (cmnd_data->redirs[i].type == REDIR_INPUT)// this part is for infile
		{
			dbg_print("Redirecting input from file: %s\n", cmnd_data->redirs[i].file);
			handle_input(cmnd_data->redirs[i].file);
		}
		else if (cmnd_data->redirs[i].type == REDIR_OUTPUT)// this is for outfile
		{
			dbg_print("Redirecting output to file: %s\n", cmnd_data->redirs[i].file);
			handle_output(cmnd_data->redirs[i].file, O_WRONLY | O_CREAT | O_TRUNC);
		}
		else if (cmnd_data->redirs[i].type == REDIR_APPEND)// this is for outfile
		{
			dbg_print("Redirecting output to file: %s\n", cmnd_data->redirs[i].file);
			handle_output(cmnd_data->redirs[i].file,  O_WRONLY | O_CREAT | O_APPEND);
		}
		else if (cmnd_data->redirs[i].type == REDIR_HERE_DOC)
		{
			dbg_print("Handling heredoc redirection with delimiter: %s\n", cmnd_data->redirs[i].file);
			handle_heredoc(cmnds, cmnd_data->redirs[i].file);
		}
		i++;
	}
}
