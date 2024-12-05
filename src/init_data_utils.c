#include "../includes/minishell.h"

int	count_commands(t_tokens *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == PIPE)
			count++;
		i++;
	}
	return (count + 1);
}

int	count_tokens(t_tokens *tokens, int *index)
{
	int	k;
	int	count;

	k = *index;
	count = 0;
	while (tokens[k].token_string && tokens[k].token_type != PIPE)
	{
		if (tokens[k].token_type >= REDIR_INPUT && \
				tokens[k].token_type <= REDIR_HERE_DOC)
			k++;
		else
			count++;
		k++;
	}
	return (count);
}

int	count_redirs(t_tokens *tokens, int *index)
{
	int	k;
	int	count;

	k = *index;
	count = 0;
	while (tokens[k].token_string && tokens[k].token_type != PIPE)
	{
		if (tokens[k].token_type >= REDIR_INPUT && \
				tokens[k].token_type <= REDIR_HERE_DOC)
		{
			k++;
			count++;
		}
		k++;
	}
	return (count);
}

