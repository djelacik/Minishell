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
}

static void	print_tokens(t_tokens *tokens)
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

static void	free_data(t_data *data)
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
		}
		i++;
	}
	free(data);
}

static void	free_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while(tokens[i].token_string)
	{
		free(tokens[i].token_string);
		i++;
	}
	free(tokens);
}


int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	(void)argc;
	(void)argv;
	t_cmnds		cmnds;
	char		*input;
	t_tokens	*tokens;
	t_data		*data;
	t_env		*env_list;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
	env_list = NULL;
	ft_bzero(&cmnds, sizeof(t_cmnds));
	init_list(&env_list, envp);
	init_list(&cmnds.env_list, envp);
	g_exit_status = 0;
	signal(SIGQUIT, handle_sigint);
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
		tokens = tokenize_input(input, &env_list);
		if (tokens)
		{
			//print_tokens(tokens);
			data = init_data(tokens);
			if (data)
			{
				cmnds.data = data;
				print_cmnds(&cmnds);
				//print_data(data);
				cmnds.command_count = cmnds.data->cmnd_count;
				start_process(&cmnds);
				free_struct_loop(&cmnds);
				free_data(data);
			}
			free_tokens(tokens);
		}
		free(input);
		if (cmnds.exited == 1)
			break;
	}
	//error_exit(&cmnds, NULL, EXIT_SUCCESS);
	free_env_list(&env_list);
	return(g_exit_status);
}
