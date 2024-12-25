/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:19:54 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:26:02 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_terminal_set(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
}

static void	init_shell(t_cmnds *cmnds, char **envp)
{
	ft_bzero(cmnds, sizeof(t_cmnds));
	init_list(&cmnds->env_list, envp);
	g_exit_status = 0;
}

static void	process_input_user(char *input, t_cmnds *cmnds)
{
	t_tokens	*tokens;
	t_data		*data;

	tokens = tokenize_input(input, &cmnds->env_list);
	if (tokens)
	{
		data = init_data(tokens);
		free_tokens(tokens);
		if (data)
		{
			cmnds->data = data;
			cmnds->command_count = cmnds->data->cmnd_count;
			print_cmnds(cmnds);
			start_process(cmnds);
			free_data(data);
		}
		free_struct_loop(cmnds);
	}
}

static char	*user_input(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	input = readline("minishell % ");
	if (!input)
		printf("exit\n");
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmnds	cmnds;
	char	*input;

	(void)argc;
	(void)argv;
	init_terminal_set();
	init_shell(&cmnds, envp);
	while (1)
	{
		input = user_input();
		if (!input)
			break ;
		add_history(input);
		process_input_user(input, &cmnds);
		free(input);
	}
	free_global(&cmnds);
	return (g_exit_status);
}
