#include "../includes/minishell.h"

static int	count_tokens(char *input)
{
	char	quote_type;
	char	*env_var;
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '\'' || input[i] == '"')
		{
			quote_type = input[i];
			i++;
			while (input[i] && input[i] != quote_type)
			{
				if (quote_type == '"' && input[i] == '$')
				{
					env_var = environment_variable(input, &i);
					if (env_var)
					{
						count += ft_strlen(env_var);
						free(env_var);
					}
				}
				else
				{
					count++;
					i++;
				}
			}
			if (input[i] == quote_type)
				i++;
		}
		else
		{
			while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"')
			{
				if (input[i] == '$')
				{
					env_var = environment_variable(input, &i);
					if (env_var)
					{
						count += ft_strlen(env_var);
						free(env_var);
					}
				}
				else
				{
					count++;
					i++;
				}
			}
		}
		count++;
	}
	return (count);
}

char *ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	i;

	dst = malloc((n + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

t_tokens	*tokenize_input(char *input)
{
	t_tokens	*tokens;
	int		token_count;
	int		i;
	int		j;
	int		start;

	token_count = count_tokens(input);
	tokens = malloc((token_count + 1) * sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break;
		if (input[i] == '>' || input[i] == '<')
		{
			tokens[j].token_string = redir_symb(input, &i, &tokens[j]);
			j++;
			continue ;
		}
		else if (input[i] == '\'' || input[i] == '"')
			tokens[j].token_string = handling_quotes(input, &i);
		else if (input[i] == '$')
			tokens[j].token_string = environment_variable(input, &i);
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"')
				i++;
			tokens[j].token_string = ft_strndup(&input[start], i - start);
		}
		if (!tokens[j].token_string)
		{
			while (j > 0)
			{
				j--;
				free(tokens[j].token_string);
			}
			free(tokens);
			return (NULL);
		}
		if (j == 0)
			tokens[j].token_type = COMMAND;
		else if (tokens[j].token_type == 0)
			tokens[j].token_type = ARGUMENT;
		j++;
	}
	tokens[j].token_string = NULL;
	return (tokens);
}
