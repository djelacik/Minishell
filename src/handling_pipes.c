#include "../includes/minishell.h"

char	*handle_pipes(char *input, int *index, t_tokens *tokens)
{
	char	*pipe;

	pipe = NULL;
	if (input[*index] == '|')
	{
		tokens->token_type = PIPES;
		pipe = ft_strndup("|", 1);
		(*index)++;
	}
	return (pipe);
}
