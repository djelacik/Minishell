/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/10 21:28:53 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_node(t_env **head, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *head;
	*head = new_node;
}

static void	init_list(t_env **head, char **envp)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			key = ft_strndup(envp[i], equal_sign - envp[i]);
			value = ft_strdup(equal_sign + 1);
			add_node(head, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

static void	ft_env(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		dbg_print("%s=%s\n", current->key, current->value);
		//dbg_print("%s\n", current->key);
		//dbg_print("%s\n", current->value);
		current = current->next;
	}
}

static void	ft_unset(t_env **head, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, (char *)key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
		}
		prev = current;
		current = current->next;
	}
}

static void ft_export(t_env **head, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;
	
	new_node = malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	current = *head;
	while (current)
	{
		current = current->next;
	}
	current->next = new_node;
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;
	
	if (argc < 2)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[1], "echo") == 0)
		exec_echo(argv);
	if (ft_strcmp(argv[1], "pwd") == 0)
		exec_pwd();
	init_list(&head, envp);
	ft_env(head);
	if (ft_strcmp(argv[1], "unset") == 0)
	{
		ft_unset(&head, (const char *)argv[2]);
		ft_env(head);
	}
	return (EXIT_SUCCESS);
}
