#include "../../includes/minishell.h"

static int	allocate_mem(t_data *data, int j, int arg_count, int redir_count)
{
	data[j].args = malloc((arg_count + 1) * sizeof(t_tokens));
	data[j].redirs = malloc((redir_count + 1) * sizeof(t_redirect));
	if (!data[j].args || !data[j].redirs)
		return (0);
	data[j].token_count = 0;
	data[j].redir_count = 0;
	return (1);
}

static void	process_redir(t_tokens *tokens, t_data *data, int *index, int j)
{
	(*index)++;
	data[j].redirs[data[j].redir_count].file = ft_strdup(tokens[*index].token_string);
	data[j].redirs[data[j].redir_count++].type = tokens[*index].token_type;
}

static void	process_args(t_tokens *tokens, t_data *data, int *index, int j)
{
	data[j].args[data[j].token_count].token_string = ft_strdup(tokens[*index].token_string);
	data[j].args[data[j].token_count].token_type = tokens[*index].token_type;
	data[j].args[data[j].token_count++].builtin_type = tokens[*index].builtin_type;
}

static int	parse_command(t_tokens *tokens, t_data *data, int *index, int j)
{
	int	arg_count;
	int	redir_count;

	arg_count = count_args(tokens, index);
	redir_count = count_redirs(tokens, index);
	if (!allocate_mem(data, j, arg_count, redir_count))
		return (0);
	while (tokens[*index].token_string && tokens[*index].token_type != PIPE)
	{
		if (tokens[*index].token_type >= REDIR_INPUT \
				&& tokens[*index].token_type <= REDIR_HERE_DOC)
			process_redir(tokens, data, index, j);
		else
			process_args(tokens, data, index, j);
		(*index)++;
	}
	data[j].args[data[j].token_count].token_string = NULL;
	data[j].redirs[data[j].redir_count].file = NULL;
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
	if (!tokens[i].token_string)
		data->cmnd_count = 0;
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
