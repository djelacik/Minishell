#include "../includes/minishell.h"

t_tokens	*tokenize_input(char *input)
{
	char	**tokens_array;
	t_tokens	*tokens;
	int	i;

	tokens_array = ft_split(input, ' ');
	tokens = malloc(10 * sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens_array[i] && i < 10)
	{
		tokens[i].token_string = tokens_array[i];
		if (i == 0)
			tokens[i].token_type = COMMAND;
		else
			tokens[i].token_type = ARGUMENT;
		i++;
	}
	free(tokens_array);
	return (tokens);
}
