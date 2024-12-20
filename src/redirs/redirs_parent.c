/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:44:46 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/20 20:46:58 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	handle_output(char *filename, int flags)
{
	int		fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(OPEN_ERR);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror(DUP2_ERR);
		return ;
	}
	close(fd);
}

void	handle_redirections_parent(t_data *cmnd_data)
{
	int		i;

	dbg_print("Handling redirections (redir_count: %d)\n", cmnd_data->redir_count);
	i = 0;
	while (i < cmnd_data->redir_count)
	{
		if (cmnd_data->redirs[i].type == REDIR_INPUT)
		{
			dbg_print("Redirecting input from file: %s\n", cmnd_data->redirs[i].file);
			handle_input(cmnd_data->redirs[i].file);
		}
		else if (cmnd_data->redirs[i].type == REDIR_OUTPUT)
		{
			dbg_print("Redirecting output to file: %s\n", cmnd_data->redirs[i].file);
			handle_output(cmnd_data->redirs[i].file,
				O_WRONLY | O_CREAT | O_TRUNC);
		}
		else if (cmnd_data->redirs[i].type == REDIR_APPEND)
		{
			dbg_print("Redirecting output to file: %s\n", cmnd_data->redirs[i].file);
			handle_output(cmnd_data->redirs[i].file,
				O_WRONLY | O_CREAT | O_APPEND);
		}
		else if (cmnd_data->redirs[i].type == REDIR_HERE_DOC)
		{
			dbg_print("Handling heredoc redirection with delimiter: %s\n", cmnd_data->redirs[i].file);
			handle_heredoc_parent(cmnd_data->redirs[i].file);
		}
		i++;
	}
}
