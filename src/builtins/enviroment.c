#include "../../includes/minishell.h"

void	init_list(t_env **head, char **envp)
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
			lst_add_back(head, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

static char	*save_pairs(char *token_string, char **value_p)
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
	return (key);
}

void	ft_env(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->value)
		{
			printf("%s=%s\n", current->key, current->value);
			// dbg_print("%s\n", current->key);
			// dbg_print("%s\n", current->value);
		}
		current = current->next;
	}
}

void	lst_add_back(t_env **head, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;
	
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_node;
}

void	rotate_add(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_node;
}

/* void	export_add(t_env **head, const char *line)
{
	t_env		*current;
	t_env		*new_node;
	char		*key;
	const char	*value;
	
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	save_pairs(line, &value);
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
} */

void	export_add(t_env **head, t_command *command)
{
	t_env		*new_node;
	char		*key;
	char		*value;
	int			i;
	
	i = 0;
	while (i < command->token_count)
	{
		key = save_pairs(command->tokens[i].token_string, &value);
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
		rotate_add(head, new_node);
		i++;
	}
}

void	ft_unset(t_env **head, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	while (current)
	{
		if (ft_strcmp((char *)current->key, (char *)key) == 0)
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
