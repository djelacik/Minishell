/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:26:53 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:28:51 by mjaakkol         ###   ########.fr       */
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
