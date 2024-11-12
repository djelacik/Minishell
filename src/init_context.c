/*#include "../includes/minishell.h"

t_context	*init_context(t_tokens *tokens)
{
	t_context	*context;
	int			i;

	context = malloc(sizeof(t_context));
	if (!context)
		return (NULL);
	context->token_count = 0;
	context->redir_count = 0;
	context->cmnd_tokens = malloc(token_count * sizeof(t_tokens));
	context->redirs = malloc(redir_count * sizeof(t_redirections));
	i = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == REDIR_INPUT || tokens[i].token_type == REDIR_OUTPUT || tokens[i].token_type == REDIR_APPEND || tokens[i].token_type == REDIR_HERE_DOC)
		{
			i++;
			context->redir_count++;
		}
		else
		{
			context->cmnd_tokens =
			i++;
		}
	}
	return (context);
}*/
