/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:54:28 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/20 10:55:43 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	setup_pids(t_cmnds *cmnds)
{
	cmnds->pids = ft_calloc(cmnds->command_count, sizeof(pid_t));
	if (!cmnds->pids)
		error_exit(cmnds, NULL, EXIT_FAILURE);
}

int	fork_process(int i, int fd_in, int pipefd[2], t_cmnds *cmnds)
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
	dbg_print("Parent process cmnds->pids[%d]\n", cmnds->pids[i]);
	signal(SIGINT, SIG_IGN);
	return (0);
}
