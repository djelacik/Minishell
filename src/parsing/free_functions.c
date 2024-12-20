/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:00:03 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:00:34 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_exist_tokens(t_tokens *tokens, int index)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (i <= index)
	{
		free(tokens[i].token_string);
		i++;
	}
	free(tokens);
}

void	free_id_and_tokens(t_id *id, t_tokens *tokens, int j)
{
	free_exist_tokens(tokens, j);
	free_id(id);
}

void	free_id(t_id *id)
{
	if (!id)
		return ;
	free(id->i);
	free(id->j);
}

void	free_data_fail(t_data *data, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		if (data[i].args)
		{
			j = 0;
			while (data[i].args[j].token_string)
				free(data[i].args[j++].token_string);
			free(data[i].args);
		}
		if (data[i].redirs)
		{
			j = 0;
			while (data[i].redirs[j].file)
				free(data[i].redirs[j++].file);
			free(data[i].redirs);
		}
		i++;
	}
	free(data);
}
