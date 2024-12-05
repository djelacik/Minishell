#include "../includes/minishell.h"

static t_data	*allocate_data(int command_count)
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

static void	free_data_fail(t_data *data, int count)
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

static int	allocate_mem(t_data *data, int j, int arg_count, int redir_count)
{
	data[j].args = malloc((arg_count + 1) * sizeof(t_tokens));
	data[j].redirs = malloc((redir_count + 1) * sizeof(t_redirect));
	if (!data[j].args || !data[j].redirs)
		return (0);
	return (1);
}

static int	parse_command(t_tokens *tokens, t_data *data, int *index, int j)
{
	int	arg_count;
	int	redir_count;
	int	args_index;
	int	redir_index;

	arg_count = count_tokens(tokens, index);
	redir_count = count_redirs(tokens, index);
	if (!allocate_mem(data, j, arg_count, redir_count))
		return (0);
	args_index = 0;
	redir_index = 0;
	while (tokens[*index].token_string && tokens[*index].token_type != PIPE)
	{
		if (tokens[*index].token_type >= REDIR_INPUT \
				&& tokens[*index].token_type <= REDIR_HERE_DOC)
		{
			(*index)++;
			data[j].redirs[redir_index].file = \
						ft_strdup(tokens[*index].token_string);
			data[j].redirs[redir_index++].type = tokens[*index].token_type;
		}
		else
		{
			data[j].args[args_index].token_string = \
								ft_strdup(tokens[*index].token_string);
			data[j].args[args_index].token_type = tokens[*index].token_type;
			data[j].args[args_index].builtin_type = tokens[*index].builtin_type;
			args_index++;
		}
		(*index)++;
	}
	data[j].args[args_index].token_string = NULL;
	data[j].redirs[redir_index].file = NULL;
	data[j].redir_count = redir_count;
	data[j].token_count = arg_count;
	return (1);
}

t_data	*init_data(t_tokens *tokens)
{
	t_data	*data;
	int		command_count;
	int		i;
	int		j;

	command_count = count_commands(tokens);
	if (command_count == 0)
		return (NULL);
	data = allocate_data(command_count);
	if (!data)
		return (NULL);
	data->cmnd_count = command_count;
	i = 0;
	j = -1;
	while (++j < command_count)
	{
		if (!parse_command(tokens, data, &i, j))
		{
			free_data_fail(data, j);
			return (NULL);
		}
		if (tokens[i].token_string && tokens[i].token_type == PIPE)
			i++;
	}
	return (data);
}

/*t_data	*init_data(t_tokens *tokens)
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
	data->cmnd_count = count + 1;
	i = 0;
	j = 0;
	if (!tokens[i].token_string)
		data->cmnd_count = 0;
	while (j < data->cmnd_count)
	{
		arg_count = 0;
		redir_count = 0;
		k = i;
		while (tokens[k].token_string && tokens[k].token_type != PIPE)
		{
			if (tokens[k].token_type == REDIR_INPUT || tokens[k].token_type == REDIR_OUTPUT || tokens[k].token_type == REDIR_APPEND || tokens[k].token_type == REDIR_HERE_DOC)
			{
				k++;
				//arg_count++;
				redir_count++;
			}
			else
				arg_count++;
			k++;
		}
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
				//data[j].token_count++;
				//data[j].args[args_index].token_string = ft_strdup(tokens[i].token_string);
				//data[j].args[args_index].token_type = tokens[i].token_type;
				//data[j].args[args_index].builtin_type = tokens[i].builtin_type;
			}
			else
			{
				data[j].token_count++;
				data[j].args[args_index].token_string = ft_strdup(tokens[i].token_string);
				data[j].args[args_index].token_type = tokens[i].token_type;
				data[j].args[args_index].builtin_type = tokens[i].builtin_type;
				args_index++;
			}
			i++;
		}
		data[j].redirs[redir_index].file = NULL;
		data[j].args[args_index].token_string = NULL;
		if (tokens[i].token_type == PIPE)
			i++;
		j++;
	}
	return (data);
}*/
