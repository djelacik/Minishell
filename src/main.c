#include "../includes/minishell.h"

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
	while (i < data->redir_count)
	{
		printf("redir[%d]: %s type: %d\n", i, data->redirs[i].arg, data->redirs[i].type);
		i++;
	}
	i = 0;
	printf("token count : %d\n", data->token_count);
	while (i < data->token_count)
	{
		printf("args[%d]: %s type: %d builtin: %d\n", i, data->args[i].token_string, data->args[i].token_type, data->args[i].builtin_type);
		i++;
	}
}

static void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->token_count)
	{
		free(data->args[i].token_string);
		i++;
	}
	free(data->args);
	i = 0;
	while (i < data->redir_count)
	{
		free(data->redirs[i].arg);
		i++;
	}
	free(data->redirs);
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

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char		*input;
	t_tokens	*tokens;
	t_data		*data;

	while (1)
	{
		input = readline("minishell % ");
		if (!input) // when user exit with Ctrl+D, readline returns NULL
			break ;
		add_history(input);
		tokens = tokenize_input(input);
		if (tokens)
		{
			print_tokens(tokens);
			data = init_data(tokens);
			if (data)
			{
				print_data(data);
				free_data(data);
			}
			free_tokens(tokens);
		}
		free(input);
	}
	return(0);
}
