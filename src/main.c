#include "../includes/minishell.h"

static void	print_tokens(t_tokens *tokens)
{
	int i;

	i = 0;
	while (tokens[i].token_string)
	{
		printf("%s ", tokens[i].token_string);
		if (tokens[i].token_type == COMMAND)
			printf("%d\n", tokens[i].token_type);
		else if (tokens[i].token_type == ARGUMENT)
			printf("%d\n", tokens[i].token_type);
		i++;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*input;
	t_tokens *tokens;
	int i;

	while (1)
	{
		input = readline("minishell % ");
		if (!input) // when user exit with Ctrl+D, readline returns NULL
			break ;
		add_history(input);
		tokens = tokenize_input(input);
		i = 0;
		if (tokens)
		{
			print_tokens(tokens);
			while (tokens[i].token_string)
				free(tokens[i++].token_string);
			free(tokens);
		}
		free(input);
	}
	return(0);
}