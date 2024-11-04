#include "../includes/minishell.h"

char	*redir_symb(char *input, int *index, t_tokens *tokens)
{
	char	*symbol;

	symbol = NULL;
	if (input[*index] == '<')
	{
		if (input[*index + 1] == '<')
		{
			tokens->token_type = REDIR_HERE_DOC;
			symbol = ft_strndup("<<", 2);
			(*index) += 2;
		}
		else
		{
			tokens->token_type = REDIR_INPUT;
			symbol = ft_strndup("<", 1);
			(*index)++;
		}
	}
	else if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
		{
			tokens->token_type = REDIR_APPEND;
			symbol = ft_strndup(">>", 2);
			(*index) += 2;
		}
		else
		{
			tokens->token_type = REDIR_OUTPUT;
			symbol = ft_strndup(">", 1);
			(*index)++;
		}
	}
	return (symbol);
}
