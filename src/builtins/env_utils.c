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
			add_node(head, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

void	add_node(t_env **head, const char *key, const char *value)
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

void	lst_add_back(t_env **head, t_env *new_node)
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
	return (key);
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

int	get_lst_size(t_env *lst)
{
	unsigned int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	lst_to_arr(t_env *head, t_cmnds *cmnds)
{
	int		i;
	t_env	*cur;
	
	i = get_lst_size(head);
	cmnds->env_cpy = ft_calloc(sizeof(char *), i + 1);
	cur = head;
	i = 0;
	while (cur)
	{
		cmnds->env_cpy[i] = ft_strjoin(cur->key, "=");
		cmnds->env_cpy[i] = ft_strjoin(cmnds->env_cpy[i],cur->value);
		cur = cur->next;
		i++;
	}
}

char	*ft_getenv(char *key, t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	ft_setenv(char *key, char *value, t_env **head)
{
	t_env	*current;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup((const char *)value);
			return ;
		}
		current = current->next;
	}
}
