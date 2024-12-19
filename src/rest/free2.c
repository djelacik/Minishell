#include "../../includes/minishell.h"

void	free_data_helper(t_data *data, int i)
{
	int	j;

	if (data[i].args)
	{
		j = 0;
		while (data[i].args[j].token_string)
		{
			free(data[i].args[j].token_string);
			j++;
		}
		free(data[i].args);
		data[i].args = NULL;
	}
	if (data[i].redirs)
	{
		j = 0;
		while (data[i].redirs[j].file)
		{
			free(data[i].redirs[j].file);
			j++;
		}
		free(data[i].redirs);
		data[i].redirs = NULL;
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (i < data->cmnd_count)
	{
		free_data_helper(data, i);
		i++;
	}
	free(data);
}

void	free_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].token_string)
	{
		printf("tokens[%d].token_string: %s\n", i, tokens[i].token_string);
		free(tokens[i].token_string);
		printf("i is: %d\n", i);
		i++;
	}
	free(tokens);
}
