#include "../includes/minishell.h"

t_data	*init_data(t_tokens *tokens)
{
	t_data		*data;
	int			i;
	int			arg_count;
	int			j;
	int			k;
	int			count;
	int			args_index;

	i = 0;
	count = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == PIPE)
			count++;
		i++;
	}
	data = malloc((count + 1)* sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_count = 0;
	data->redir_count = 0;
	data->cmnd_count = 1;
	i = 0;
	while (tokens[i].token_string)
	{
		if (tokens[i].token_type == REDIR_INPUT || tokens[i].token_type == REDIR_OUTPUT || tokens[i].token_type == REDIR_APPEND || tokens[i].token_type == REDIR_HERE_DOC)
		{
			//data->token_count++;
			i++;
			data->redir_count++;
			data->token_count++;
		}
		if (tokens[i].token_type == PIPE)
			data->cmnd_count++;
		else
			data->token_count++;
		i++;
	}
	i = 0;
	args_index = 0;
	j = 0;
	while (j < data->cmnd_count)
	{
		arg_count = 0;
		k = i;
		while (tokens[k].token_string && tokens[k].token_type != PIPE)
		{
			printf("string: %s\n", tokens[k].token_string);
			if (tokens[k].token_type == REDIR_INPUT || tokens[k].token_type == REDIR_OUTPUT || tokens[k].token_type == REDIR_APPEND || tokens[k].token_type == REDIR_HERE_DOC)
			{
				k++;
				arg_count++;
			}
			else
				arg_count++;
			k++;
		}
		printf("arg count: %d\n", arg_count);
		data[j].args = malloc((arg_count + 1) * sizeof(t_tokens));
		if (!data[j].args)
		{
			while (--j >= 0)
				free(data[j].args);
			free(data);
			return (NULL);
		}
		args_index = 0;
		while (tokens[i].token_string && tokens[i].token_type != PIPE)
		{
			if (tokens[i].token_type == REDIR_INPUT || tokens[i].token_type == REDIR_OUTPUT || tokens[i].token_type == REDIR_APPEND || tokens[i].token_type == REDIR_HERE_DOC)
			{
				i++;
				data[j].args[args_index].token_string = ft_strdup(tokens[i].token_string);
				data[j].args[args_index].token_type = tokens[i].token_type;
				data[j].args[args_index].builtin_type = tokens[i].builtin_type;
			}
			else
			{	
				data[j].args[args_index].token_string = ft_strdup(tokens[i].token_string);
				data[j].args[args_index].token_type = tokens[i].token_type;
				data[j].args[args_index].builtin_type = tokens[i].builtin_type;
			}
			args_index++;
			i++;
		}
		data[j].args[args_index].token_string = NULL;
		if (tokens[i].token_type == PIPE)
			i++;
		j++;
	}
	return (data);
}
