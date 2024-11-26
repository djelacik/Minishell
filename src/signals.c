<<<<<<< HEAD
/*#include "../includes/minishell.h"
=======
#include "../includes/minishell.h"
>>>>>>> origin

void	handle_sigint(int sig) // ctrl-c
{
	if (sig == SIGINT)
	{
<<<<<<< HEAD
=======
		//rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		//rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		//write(STDOUT_FILENO, "", 0);
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "", 0);
>>>>>>> origin
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
<<<<<<< HEAD
}*/




=======
}
>>>>>>> origin
