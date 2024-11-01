#include "../includes/minishell.h"

int	calculate_single_len(char *input, int start_index, char quote_type)
{
	int	len;
	int	i;

	len = 0;
	i = start_index + 1;
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
	int		quoted_len;
	int		i;

	quoted_len = calculate_single_len(input, *index, '\'');
	quoted_input = malloc((quoted_len + 1) * sizeof(char));
	if (!quoted_input)
		return (NULL);
	(*index)++;
	i = 0;
	while (input[*index] && input[*index] != '\'')
	{
		quoted_input[i++] = input[*index];
		(*index)++;
	}
	quoted_input[i] = '\0';
	if (input[*index] == '\'')
		(*index)++;
	return (quoted_input);
}

int calculate_double_len(char *input, int start_index, char quote_type)
{
	char	*env_var;
	int	len;
	int	i;

	len = 0;
	i = start_index + 1;
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
	int		quoted_len;
	int		i;
	int		j;

	quoted_len = calculate_double_len(input, *index, '"');
	quoted_input = malloc((quoted_len + 1) * sizeof(char));
	if (!quoted_input)
		return (NULL);
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
		/*else if (input[*index] == '\\' && (input[*index + 1] == '$' || input[*index + 1] == '"'))
		{
			(*index)++;
			quoted_input[i++] = input[*index];
		}*/
		else
			quoted_input[i++] = input[*index];
		(*index)++;
	}
	quoted_input[i] = '\0';
	if (input[*index] == '"')
		(*index)++;
	return (quoted_input);
}

char	*handling_quotes(char *input, int *index)
{
	if (input[*index] == '\'')
		return (single_quotes(input, index));
	else if (input[*index] == '"')
		return (double_quotes(input, index));
	return (NULL);
}
