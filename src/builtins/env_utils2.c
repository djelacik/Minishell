#include "../../includes/minishell.h"

void	update_env_cpy(t_cmnds *cmnds)
{
	int		i;
	t_env	*cur;
	
	if (cmnds->env_cpy)
		free_array(cmnds->env_cpy);
	cur = cmnds->env_list;
	i = get_lst_size(cur);
	cmnds->env_cpy = ft_calloc(sizeof(char *), i + 1);
	if (!cmnds->env_cpy)
	{
		perror(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (cur)
	{
		cmnds->env_cpy[i] = ft_strjoin(cur->key, "=");
		if (!cmnds->env_cpy[i])
		{
			perror(MALLOC_ERR);
			exit(EXIT_FAILURE);
		}
		cmnds->env_cpy[i] = ft_strjoin(cmnds->env_cpy[i],cur->value);
		if (!cmnds->env_cpy[i])
		{
			perror(MALLOC_ERR);
			exit(EXIT_FAILURE);
		}
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
