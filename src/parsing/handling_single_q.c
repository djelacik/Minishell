#include "../../includes/minishell.h"

static char	*extract_single_input(char *input, int *index)
{
	char	*quoted_input;
	int		quoted_len;
	int		i;

	quoted_len = calculate_single_len(input, *index, '\'');
	quoted_input = malloc((quoted_len + 1) * sizeof(char));
	if (!quoted_input)
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
	if (input[*index] != '\'')
	{
		free(quoted_input);
		return (NULL);
	}
	return (quoted_input);
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

	if (calculate_quotes_single(input) == 0)
		return (NULL);
	parsed = NULL;
	quoted_input = extract_single_input(input, index);
	if (!quoted_input)
		return (NULL);
	parsed = ft_strdup(quoted_input);
	free(quoted_input);
	if (input[*index] == '\'')
		(*index)++;
	return (parsed);
}
