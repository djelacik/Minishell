/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:30:34 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:38:03 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(t_env **head)
{
	t_env	*current;
	t_env	*next_node;

	current = *head;
	while (current)
	{
		next_node = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next_node;
	}
	*head = NULL;
}

static void	free_data_s(t_data *data)
{
	int		i;

	i = 0;
	if (data->args)
	{
		while (i < data->token_count)
		{
			if (data->args[i].token_string)
				free(data->args[i].token_string);
			i++;
		}
		free(data->args);
	}
	i = 0;
	if (data->redirs)
	{
		while (i < data->redir_count)
		{
			free(data->redirs[i].file);
			i++;
		}
		free(data->redirs);
	}
}

void	free_structs(t_cmnds *cmnds)
{
	int		i;

	if (!cmnds)
		return ;
	i = 0;
	while (i < cmnds->command_count)
	{
		free_data_s(&cmnds->data[i]);
		i++;
	}
	free(cmnds->data);
	free_env_list(&cmnds->env_list);
	free_array(cmnds->env_cpy);
	if (cmnds->pids)
	{
		free(cmnds->pids);
		cmnds->pids = NULL;
	}
}

void	free_struct_loop(t_cmnds *cmnds)
{
	if (!cmnds)
		return ;
	free(cmnds->pids);
}
