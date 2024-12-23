/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:25:11 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/20 20:47:29 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	execute_process(int i, int fd_in, t_cmnds *cmnds)
{
	int		pipe_fd[2];

	setup_pipes(i, cmnds->command_count, pipe_fd);
	signal(SIGINT, here_doc_sig);
	if (fork_process(i, fd_in, pipe_fd, cmnds) == -1)
		error_exit(cmnds, FORK_ERR, EXIT_FAILURE);
	if (fd_in != STDIN_FILENO)
	{
		dbg_print("Parent closing fd_in: %d\n", fd_in);
		close(fd_in);
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

static void	execute_in_parent(t_data *data, t_cmnds *cmnds)
{
	cmnds->saved_stdin = dup(STDIN_FILENO);
	cmnds->saved_stdout = dup(STDOUT_FILENO);
	handle_redirections_parent(data);
	execute_builtin(data, cmnds);
	dup2(cmnds->saved_stdin, STDIN_FILENO);
	dup2(cmnds->saved_stdout, STDOUT_FILENO);
	close(cmnds->saved_stdin);
	close(cmnds->saved_stdout);
}

static int	should_execute_in_parent(t_data *data, int command_count)
{
	if (command_count == 1 && is_builtin(data->args[0].token_string))
		return (1);
	return (0);
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
	if (cmnds->pids)
		wait_for_children(cmnds);
}
