#include "../../includes/minishell.h"

void	ft_env(t_env *head)
{
	t_env	*current;

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

void	export_add(t_env **head, t_command *command)
{
	t_env		*new_node;
	char		*key;
	char		*value;
	int			i;
	
	i = 1;
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
		lst_add_back(head, new_node);
		i++;
	}
}

void	single_unset(t_env **head, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
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

void	ft_unset(t_env **head, t_command *command)
{
	int		i;
	char	*value;

	if (command->token_count > 2)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	i = 1;
	while (i < command->token_count)
	{
		single_unset(head, command->tokens[i].token_string);
		i++;
	}
}

void	export_print(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->value == NULL || current->value[0] == '\0')
		{
			printf("%s=''\n", current->key);
		}
		else
		{
			printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}


