/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:08:57 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:09:29 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_redir(t_tokens *tokens, t_data *data, int *index, int j)
{
	(*index)++;
	data[j].redirs[data[j].redir_count].file = \
						ft_strdup(tokens[*index].token_string);
	data[j].redirs[data[j].redir_count++].type = tokens[*index - 1].token_type;
}

static void	process_args(t_tokens *tokens, t_data *data, int *index, int j)
{
	data[j].args[data[j].token_count].token_string = \
						ft_strdup(tokens[*index].token_string);
	data[j].args[data[j].token_count].token_type = tokens[*index].token_type;
	data[j].args[data[j].token_count++].builtin_type = \
						tokens[*index].builtin_type;
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

static int	handle_parse_commands(t_tokens *tokens, t_data *data, \
		int *i, int command_count)
{
	int	j;

	j = 0;
	while (j < command_count)
	{
		if (!parse_command(tokens, data, i, j))
		{
			free_data_fail(data, j);
			return (0);
		}
		if (tokens[*i].token_string && tokens[*i].token_type == PIPE)
			(*i)++;
		j++;
	}
	return (1);
}

t_data	*init_data(t_tokens *tokens)
{
	t_data	*data;
	int		command_count;
	int		i;

	command_count = count_commands(tokens);
	if (command_count == 0)
		return (NULL);
	data = allocate_data(command_count);
	if (!data)
		return (NULL);
	data->cmnd_count = command_count;
	i = 0;
	if (!tokens[i].token_string)
		data->cmnd_count = 0;
	if (!handle_parse_commands(tokens, data, &i, command_count))
		return (NULL);
	return (data);
}
