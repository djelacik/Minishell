/*#include "../includes/minishell.h"

t_tarray	*tokens_to_array(t_tokens *tokens)
{
	t_tarray	*array;
	int			count_of_tokens;
	int			i;
	int			j;

	count_of_tokens = 0;
	while (tokens[count_of_tokens].token_string)
		count_of_tokens++;
	array = malloc(sizeof(t_tarray));
	if (!array)
		return (NULL);
	array->token_count = count_of_tokens;
	array->token_array = malloc((count_of_tokens + 1) * sizeof(t_tokens *));
	if (!array->token_array)
	{
		free(array);
		return (NULL);
	}
	i = 0;
	while (i < count_of_tokens)
	{
		array->token_array[i] = malloc(sizeof(t_tokens));
		if (!array->token_array[i])
		{
			j = 0;
			while (j < i)
			{
				free(array->token_array[j]);
				j++;
			}
			free(array->token_array);
			free(array);
			return (NULL);
		}
		array->token_array[i]->token_string = ft_strdup(tokens[i].token_string);
		array->token_array[i]->token_type = tokens[i].token_type;
		array->token_array[i]->builtin_type = tokens[i].builtin_type;
		i++;
	}
	array->token_array[count_of_tokens] = NULL;
	return (array);
}*/	
