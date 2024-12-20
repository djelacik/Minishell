/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:00:34 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/20 10:00:44 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env *head)
{
	t_env	*current;

	dbg_print("Executing ft_env\n");
	current = head;
	while (current)
	{
		if (current->value)
		{
			printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}

void	single_unset(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	dbg_print("Executing single_unset for key: %s\n", key);
	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			dbg_print("Key found: %s, removing it\n", current->key);
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	dbg_print("Key not found: %s\n", key);
}

void	ft_unset(t_env **head, t_data *data)
{
	int		i;

	dbg_print("Executing ft_unset\n");
	if (data->token_count < 2)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	i = 1;
	while (i < data->token_count)
	{
		dbg_print("Unsetting key: %s\n", data->args[i].token_string);
		single_unset(head, data->args[i].token_string);
		i++;
	}
}
