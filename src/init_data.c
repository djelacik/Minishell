#include "../includes/minishell.h"

t_data	*init_data(t_tokens *tokens)
{
	t_data		*data;
	int			i;
	int			redir_index;
	int			args_index;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_count = 0;
	data->redir_count = 0;
	i = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == REDIR_INPUT || tokens[i].token_type == REDIR_OUTPUT || tokens[i].token_type == REDIR_APPEND || tokens[i].token_type == REDIR_HERE_DOC)
		{
			data->token_count++;
			i++;
			data->redir_count++;
			data->token_count++;
		}
		else
			data->token_count++;
		i++;
	}
	data->args = malloc((data->token_count + 1) * sizeof(t_tokens));
	if (!data->args)
	{
		free(data);
		return (NULL);
	}
	data->redirs = malloc((data->redir_count + 1) * sizeof(t_redirect));
	if (!data->redirs)
	{
		free(data->args);
		free(data);
		return (NULL);
	}
	i = 0;
	redir_index = 0;
	args_index = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == REDIR_INPUT || tokens[i].token_type == REDIR_OUTPUT || tokens[i].token_type == REDIR_APPEND || tokens[i].token_type == REDIR_HERE_DOC)
		{
			data->args[args_index].token_string = ft_strdup(tokens[i].token_string);
			data->args[args_index].token_type = tokens[i].token_type;
			args_index++;
			i++;
			data->redirs[redir_index].arg = ft_strdup(tokens[i].token_string);
			data->redirs[redir_index].type = tokens[i].token_type;
			data->args[args_index].token_string = ft_strdup(tokens[i].token_string);
			data->args[args_index].token_type = tokens[i].token_type;
			redir_index++;
			args_index++;
		}
		else
		{
			data->args[args_index].token_string = ft_strdup(tokens[i].token_string);
			data->args[args_index].token_type = tokens[i].token_type;
			data->args[args_index].builtin_type = tokens[i].builtin_type;
			args_index++;
		}
		i++;
	}
	data->args[args_index].token_string = NULL;
	data->redirs[redir_index].arg = NULL;
	return (data);
}
