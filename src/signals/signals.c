/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:26:53 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:52:03 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	here_doc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		exit(130);
	}
}

void	wait_for_children(t_cmnds *cmnds)
{
	int		i;
	int		status;
	int		signal_num;

	status = 0;
	i = 0;
	while (i < cmnds->command_count)
	{
		waitpid(cmnds->pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			if (g_exit_status == 1)
				g_exit_status = 1;
			else
				g_exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			signal_num = WTERMSIG(status);
			if (signal_num == SIGINT)
				g_exit_status = 130;
		}
		i++;
	}
}
