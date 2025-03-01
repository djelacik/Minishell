/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:35:53 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/20 10:37:14 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		dbg_print("Checking if fd_in is valid: %d\n", fcntl(fd_in, F_GETFD));
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror(DUP2_ERR);
			exit(EXIT_FAILURE);
		}
		dbg_print("Closing fd_in: %d\n", fd_in);
		close(fd_in);
	}
	if (pipe_fd[1] != -1)
	{
		dbg_print("Redirecting output (pipe_fd[1]: %d -> STDOUT_FILENO)\n", pipe_fd[1]);
		dbg_print("Checking if pipe_fd[1] is valid: %d\n", fcntl(pipe_fd[1], F_GETFD));
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror(DUP2_ERR);
			exit(EXIT_FAILURE);
		}
		dbg_print("Closing pipe_fd[1]: %d\n", pipe_fd[1]);
		close(pipe_fd[1]);
	}
}

static void	execute_child_command(int i, t_cmnds *cmnds)
{
	dbg_print("Child process %d handling redirections\n", i);
	handle_redirections(&cmnds->data[i], cmnds);
	dbg_print("Child process %d executing command: %s\n", i, cmnds->data[i].args[0].token_string);
	close_unused_fds();
	if (is_builtin(cmnds->data[i].args[0].token_string))
	{
		dbg_print("Executing builtin command: %s\n\n", cmnds->data[i].args[0].token_string);
		execute_builtin(&cmnds->data[i], cmnds);
		error_exit(cmnds, NULL, EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execute_external(&cmnds->data[i], cmnds);
		perror(EXEC_ERR);
		exit(EXIT_FAILURE);
	}
}

void	child_process(int i, int fd_in, int pipe_fd[2], t_cmnds *cmnds)
{
	dbg_print("Child process %d setting up input/output redirections\n", i);
	cmnds->saved_stdin = dup(STDIN_FILENO);
	cmnds->saved_stdout = dup(STDOUT_FILENO);
	setup_input_output(fd_in, pipe_fd);
	dbg_print("Child process %d starting command execution\n", i);
	execute_child_command(i, cmnds);
}
