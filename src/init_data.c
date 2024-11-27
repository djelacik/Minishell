#include "../includes/minishell.h"

t_data	*init_data(t_tokens *tokens)
{
	t_data		*data;
	int			i;
	int			arg_count;
	int			redir_count;
	int			j;
	int			k;
	int			count;
	int			args_index;
	int			redir_index;

	i = 0;
	count = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == PIPE)
			count++;
		i++;
	}
	data = malloc((count + 1) * sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_count = 0;
	data->redir_count = 0;
	data->cmnd_count = 1;
	i = 0;
	redir_count = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == REDIR_INPUT || tokens[i].token_type == REDIR_OUTPUT || tokens[i].token_type == REDIR_APPEND || tokens[i].token_type == REDIR_HERE_DOC)
		{
			i++;
			redir_count++;
		}
		if (tokens[i].token_type == PIPE)
			data->cmnd_count++;
		i++;
	}
	/*data->redirs = malloc((redir_count + 1) * sizeof(t_redirect));
	if (!data->redirs)
	{
		free(data);
		return (NULL);
	}*/
	i = 0;
	//args_index = 0;
	//redir_index = 0;
	j = 0;
	redir_count = 0;
	while (j < data->cmnd_count)
	{
		arg_count = 0;
		redir_count = 0;
		k = i;
		while (tokens[k].token_string && tokens[k].token_type != PIPE)
		{
			//printf("string: %s\n", tokens[k].token_string);
			if (tokens[k].token_type == REDIR_INPUT || tokens[k].token_type == REDIR_OUTPUT || tokens[k].token_type == REDIR_APPEND || tokens[k].token_type == REDIR_HERE_DOC)
			{
				k++;
				arg_count++;
				redir_count++;
			}
			else
				arg_count++;
			k++;
		}
		//printf("arg count: %d\n", arg_count);
		//printf("redir count: %d\n", redir_count);
		data[j].args = malloc((arg_count + 1) * sizeof(t_tokens));
		data[j].redirs = malloc((redir_count + 1) * sizeof(t_redirect));
		if (!data[j].args || !data[j].redirs)
		{
			while (--j >= 0)
			{
				free(data[j].args);
				free(data[j].redirs);
			}
			free(data);
			return (NULL);
		}
		args_index = 0;
		redir_index = 0;
		data[j].redir_count = 0;
		data[j].token_count = 0;
		while (tokens[i].token_string && tokens[i].token_type != PIPE)
		{
			if (tokens[i].token_type == REDIR_INPUT || tokens[i].token_type == REDIR_OUTPUT || tokens[i].token_type == REDIR_APPEND || tokens[i].token_type == REDIR_HERE_DOC)
			{
				i++;
				data[j].redir_count++;
				data[j].redirs[redir_index].file = ft_strdup(tokens[i].token_string);
				data[j].redirs[redir_index].type = tokens[i].token_type;
				redir_index++;
				data[j].token_count++;
				data[j].args[args_index].token_string = ft_strdup(tokens[i].token_string);
				data[j].args[args_index].token_type = tokens[i].token_type;
				data[j].args[args_index].builtin_type = tokens[i].builtin_type;
			}
			else
			{
				data[j].token_count++;
				data[j].args[args_index].token_string = ft_strdup(tokens[i].token_string);
				data[j].args[args_index].token_type = tokens[i].token_type;
				data[j].args[args_index].builtin_type = tokens[i].builtin_type;
			}
			args_index++;
			i++;
		}
		data[j].redirs[redir_index].file = NULL;
		data[j].args[args_index].token_string = NULL;
		if (tokens[i].token_type == PIPE)
			i++;
		j++;
	}
	return (data);
}
