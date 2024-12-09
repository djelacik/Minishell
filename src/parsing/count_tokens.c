#include "../../includes/minishell.h"

int	count_quoted_tokens(char *input, int *i, char quote_type, t_env **env_list)
{
	char	*env_var;
	int		count;

	count = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
	{
		if (quote_type == '"' && input[*i] == '$')
		{
			env_var = environment_variable(input, i, env_list);
			if (env_var)
			{
				count += ft_strlen(env_var);
				free(env_var);
			}
		}
		else
		{
			count++;
			(*i)++;
		}
	}
	if (input[*i] == quote_type)
		(*i)++;
	return (count);
}

int	count_unquoted_tokens(char *input, int *i, t_env **env_list)
{
	char	*env_var;
	int		count;

	count = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			env_var = environment_variable(input, i, env_list);
			if (env_var)
			{
				count += ft_strlen(env_var);
				free(env_var);
			}
		}
		else
		{
			count++;
			(*i)++;
		}
	}
	return (count);
}

int	count_tokens(char *input, t_env **env_list)
{
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
			count += count_quoted_tokens(input, &i, input[i], env_list);
		else
			count += count_unquoted_tokens(input, &i, env_list);
		count++;
	}
	return (count);
}
