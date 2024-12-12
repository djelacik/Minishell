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

void	single_unset(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	dbg_print("Executing single_unset for key: %s\n", key);
	current = *head;
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

void	export_print(t_env *head)
{
	t_env	*current;

	dbg_print("Executing export_print\n");
	current = head;
	while (current)
	{
		if (current->value == NULL || current->value[0] == '\0')
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
