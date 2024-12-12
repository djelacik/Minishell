#include "../../includes/minishell.h"

static void	initialize_env_cpy(t_cmnds *cmnds)
{
	int size;

	if (cmnds->env_cpy)
		free_array(cmnds->env_cpy);
	size = get_lst_size(cmnds->env_list);
	cmnds->env_cpy = ft_calloc(sizeof(char *), size + 1);
	if (!cmnds->env_cpy)
		error_exit(cmnds, NULL, EXIT_FAILURE);
}

static void	copy_env_variables(t_cmnds *cmnds)
{
	t_env	*cur;
	int		i;
	char	*value;
	char	*temp;

	cur = cmnds->env_list;
	i = 0;
	while (cur)
	{
		temp = ft_strjoin(cur->key, "=");
		if (!temp)
			error_exit(cmnds, NULL, EXIT_FAILURE);
		if (cur->value != NULL)
			value = cur->value;
		else
			value = "";
		cmnds->env_cpy[i] = ft_strjoin(temp, value);
		free(temp);
		if (!cmnds->env_cpy[i])
			error_exit(cmnds, NULL, EXIT_FAILURE);
		
		cur = cur->next;
		i++;
	}
}

void	update_env_cpy(t_cmnds *cmnds)
{
	initialize_env_cpy(cmnds);
	copy_env_variables(cmnds);
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
