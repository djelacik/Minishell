#include "../../includes/minishell.h"

/* static void	swap_nodes(t_env **prev, t_env **current, t_env **next, t_env **head)
{
	if (*prev)
		(*prev)->next = *next;
	else
		*head = *next;
	(*current)->next = (*next)->next;
	(*next)->next = *current;
	*prev = *next;
}

static int	sort_iteration(t_env **head)
{
	t_env	*current;
	t_env	*prev;
	t_env	*next;
	int		sorted;

	prev = NULL;
	current = *head;
	sorted = 1;
	while (current && current->next)
	{
		next = current->next;
		if (ft_strcmp(current->key, next->key) > 0)
		{
			swap_nodes(&prev, &current, &next, head);
			sorted = 0;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (sorted);
}

static t_env	*sort_list(t_env *head)
{
	while (!sort_iteration(&head))
		;
	return (head);
}
 */
void	export_print(t_env *head)
{
	t_env	*current;

	dbg_print("Executing export_print\n");
	//current = sort_list(head);
    current = head;

	while (current)
	{
		if (current->value == NULL )
		{
			//dbg_print("Printing key with empty value: %s=''\n", current->key);
			printf("declare -x %s\n", current->key);
		}
		else
		{
			//dbg_print("Printing key-value pair: %s=%s\n", current->key, current->value);
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
	i = 1;
	while (i < data->token_count)
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
		i++;
	}
}

