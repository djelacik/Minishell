#include "../includes/minishell.h"

int	calculate_quotes_double(char *input)
{
	int	i;
	int quote_count;

	i = 0;
	quote_count = 0;
	while (input[i])
	{
		if (input[i] == '"')
			quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		return (0);
	return (1);
}

int	calculate_quotes_single(char *input)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		return (0);
	return (1);
}

int	calculate_single_len(char *input, int start_index, char quote_type)
{
	int	len;
	int	i;

	len = 0;
	i = start_index;
	while (input[i] && input[i] == quote_type)
		i++;
	while (input[i] && input[i] != quote_type)
	{
		len++;
		i++;
	}
	return (len);
}

char	*single_quotes(char *input, int *index)
{
	char	*quoted_input;
	char	*parsed;
	int		quoted_len;
	int		i;

	parsed = NULL;
	quoted_len = calculate_single_len(input, *index, '\'');
	quoted_input = malloc((quoted_len + 1) * sizeof(char));
	if (!quoted_input)
		return (NULL);
	if (calculate_quotes_single(input) == 0)
		return (NULL);
	if (input[*index] && input[*index] == '\'')
		(*index)++;
	i = 0;
	while (input[*index] && input[*index] != '\'')
	{
		quoted_input[i++] = input[*index];
		(*index)++;
	}
	quoted_input[i] = '\0';
	parsed = ft_strdup(quoted_input);
	free(quoted_input);
	if (input[*index] != '\'')
		return (NULL);
	while (input[*index] == '\'')
		(*index)++;
	return (parsed);
}

int calculate_double_len(char *input, int start_index, char quote_type)
{
	char	*env_var;
	int	len;
	int	i;

	len = 0;
	i = start_index;
	while (input[i] && input[i] == quote_type)
		i++;
	while (input[i] && input[i] != quote_type)
	{
		if (input[i] == '$')
		{
			env_var = environment_variable(input, &i);
			if (env_var)
			{
				len += ft_strlen(env_var);
				free(env_var);
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*double_quotes(char *input, int *index)
{
	char	*quoted_input;
	char	*env_var;
	char	*parsed;
	int		quoted_len;
	int		i;
	int		j;

	parsed = NULL;
	quoted_len = calculate_double_len(input, *index, '"');
	quoted_input = malloc((quoted_len + 1) * sizeof(char));
	if (!quoted_input)
		return (NULL);
	/*if (calculate_quotes_double(input) == 0)
		return (NULL);*/
	if (input[*index] && input[*index] == '"')
		(*index)++;
	i = 0;
	while (input[*index] && input[*index] != '"')
	{
		if (input[*index] == '$')
		{
			env_var = environment_variable(input, index);
			if (env_var)
			{
				j = 0;
				while (env_var[j])
					quoted_input[i++] = env_var[j++];
				free(env_var);
				continue ;
			}
		}
		else
			quoted_input[i++] = input[*index];
		(*index)++;
	}
	quoted_input[i] = '\0';
	parsed = ft_strdup(quoted_input);
	free(quoted_input);
	/*if (input[*index] != '"')
		return (NULL);*/
	while (input[*index] == '"')
		(*index)++;
	return (parsed);
}
