#include "../../includes/minishell.h"

void	init_tokens(t_tokens *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		tokens[i].token_string = NULL;
		i++;
	}
}

int	init_id_and_tokens(t_id *id, t_tokens **tokens, char *input, t_env **env_list)
{
	int	token_count;

	token_count = count_tokens(input, env_list);
	*tokens = malloc((token_count + 1) * sizeof(t_tokens));
	if (!*tokens)
		return (-1);
	init_tokens(*tokens, token_count + 1);
	id->tokens = *tokens;
	id->i = malloc(sizeof(int));
	id->j = malloc(sizeof(int));
	if (!id->j || !id->i)
	{
		free_id_and_tokens(id, *tokens, 0);
		return (-1);
	}
	*id->i = 0;
	*id->j = 0;
	return (0);
}