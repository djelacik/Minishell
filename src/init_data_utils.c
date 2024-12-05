#include "../includes/minishell.h"

t_data	*allocate_data(int command_count)
{
	t_data	*data;
	int		i;

	data = malloc(command_count * sizeof(t_data));
	if (!data)
		return (NULL);
	i = 0;
	while (i < command_count)
	{
		data[i].args = NULL;
		data[i].redirs = NULL;
		data[i].token_count = 0;
		data[i].redir_count = 0;
		i++;
	}
	return (data);
}

void	free_data_fail(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (data[i].args)
			free(data[i].args);
		if (data[i].redirs)
			free(data[i].redirs);
		i++;
	}
	free(data);
}

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

int	count_args(t_tokens *tokens, int *index)
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

