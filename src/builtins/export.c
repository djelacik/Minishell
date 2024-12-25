/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:10:14 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/20 10:12:28 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_print(t_env *head)
{
	t_env	*current;

	dbg_print("Executing export_print\n");
	current = head;
	while (current)
	{
		if (current->value == NULL )
		{
			printf("declare -x %s\n", current->key);
		}
		else
		{
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		}
		current = current->next;
	}
}

char	*save_pairs(char *token_string, char **value_p)
{
	char	*equal_sign;
	char	*key;

	key = NULL;
	equal_sign = ft_strchr(token_string, '=');
	if (equal_sign)
	{
		key = ft_strndup(token_string, equal_sign - token_string);
		*value_p = ft_strndup(equal_sign + 1, ft_strlen(equal_sign + 1));
	}
	else
	{
		key = ft_strdup(token_string);
		*value_p = NULL;
	}
	if ((!ft_isalpha(key[0]) && key[0] != '_')
		|| !ft_isalnum_or_underscore(key))
	{
		printf("'%s': not a valid identifier\n", token_string);
		g_exit_status = 1;
		free(key);
		free(*value_p);
		return (NULL);
	}
	return (key);
}

void	export_add(t_env **head, t_data *data)
{
	t_env		*new_node;
	char		*key;
	char		*value;
	int			i;

	dbg_print("Executing export_add\n");
	i = 0;
	while (++i < data->token_count)
	{
		dbg_print("Processing token: %s\n", data->args[i].token_string);
		key = save_pairs(data->args[i].token_string, &value);
		if (!key)
			return ;
		dbg_print("Parsed key: %s, value: %s\n", key, value ? value : "NULL");
		single_unset(head, key);
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		new_node->key = key;
		if (value == NULL)
			new_node->value = NULL;
		else if (value[0] == '\0')
			new_node->value = ft_strdup("");
		else
			new_node->value = value;
		new_node->next = NULL;
		lst_add_back(head, new_node);
		dbg_print("Added new node: %s=%s\n", new_node->key, new_node->value ? new_node->value : "NULL");
	}
}
