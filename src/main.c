#include "../includes/minishell.h"

/*static void	print_cmnd_args(t_data *data, int index)
{
	int	i;

	i = 0;
	while (data[index].args[i].token_string)
	{
		printf("args[%d]: %s type: %d builtin: %d\n", i, data[index].args[i].token_string, data[index].args[i].token_type, data[index].args[i].builtin_type);
		i++;
	}
}*/

/*static void	print_tokens(t_tokens *tokens)
{
	int i;

	i = 0;
	while (tokens[i].token_string)
	{
		printf("%s ", tokens[i].token_string);
		if (tokens[i].token_type == COMMAND)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == ARGUMENT)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_INPUT)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_OUTPUT)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_APPEND)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_HERE_DOC)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == PIPE)
			printf("token type: %d, builtin type %d\n", tokens[i].token_type, tokens[i].builtin_type);
		i++;
	}
}

static void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("redir count: %d\n", data->redir_count);
	printf("command count: %d\n", data->cmnd_count);
	printf("token count : %d\n", data->token_count);
	while (i < data->cmnd_count)
	{
		print_cmnd_args(data, i);
		i++;
	}

}*/

/*static void	free_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data)
		return ;
	while (i < data->cmnd_count)
	{
		if (data[i].args)
		{
			j = 0;
			while (data[i].args[j].token_string)
			{
				free(data[i].args[j].token_string);
				j++;
			}
			free(data[i].args);
			data[i].args = NULL;
		}
		if (data[i].redirs)
		{
			j = 0;
			while (data[i].redirs[j].file)
			{
				free(data[i].redirs[j].file);
				j++;
			}
			free(data[i].redirs);
			data[i].redirs = NULL;
		}
		i++;
	}
	free(data);
}*/

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

/*int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	(void)argc;
	(void)argv;
	t_cmnds		cmnds;
	char		*input;
	t_tokens	*tokens;
	t_data		*data;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
	ft_bzero(&cmnds, sizeof(t_cmnds));
	init_list(&cmnds.env_list, envp);
	g_exit_status = 0;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		input = readline("minishell % ");
		if (!input) // when user exit with Ctrl+D, readline returns NULL
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		tokens = tokenize_input(input, &cmnds.env_list);
		if (tokens)
		{
			print_tokens(tokens);
			data = init_data(tokens);
			free_tokens(tokens);
			if (data)
			{
				cmnds.data = data;
				//print_cmnds(&cmnds);
				print_data(data);
				cmnds.command_count = cmnds.data->cmnd_count;
				start_process(&cmnds);
				free_data(data);
			}
			free_struct_loop(&cmnds);
		}
		free(input);
	}
	free_global(&cmnds);
	return(g_exit_status);
}*/
