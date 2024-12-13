#include "../includes/minishell.h"

int	g_exit_status;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		printf("Sigint??\n");
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_exit_status = 131;
}

void here_doc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		//write(1, "\n", 1);
		printf("Control C??\n");
		rl_replace_line("", 0);
		exit(130);
	}
}
