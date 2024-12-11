#include "../../includes/minishell.h"

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

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}


static void	free_tokens(t_tokens *tokens, int token_count)
{
	int		i;

	i = 0;
	while (i < token_count)
	{
		free(tokens[i].token_string);
		i++;
	}
	free(tokens);
}

static void	free_data(t_data *data)
{
	int		i;

	if (data->args)
	{
		free_tokens(data->args, data->token_count);
	}
	i = 0;
	if (data->redirs)
	{
		while (i < data->redir_count)
		{
			free(data->redirs[i].file);
			i++;
		}
		free(data->redirs);
	}
}

void	free_structs(t_cmnds *cmnds)
{
	int		i;

	if (!cmnds)
		return ;
	i = 0;
	while (i < cmnds->command_count)
	{
		free_data(&cmnds->data[i]);
		i++;
	}
	free(cmnds->data);
	free_env_list(&cmnds->env_list);
	free_array(cmnds->env_cpy);
	free(cmnds->pids);
}

int	error_exit(t_cmnds *cmnds, char *error_msg, int error_code)
{
	free_structs(cmnds);
	if (error_msg)
		printf("%s\n", error_msg);
	exit(error_code);
}
