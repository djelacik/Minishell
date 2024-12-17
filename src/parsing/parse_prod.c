#include "../../includes/minishell.h"

void	dollar_last(char *input, t_id *id, int start)
{
	char	*temp;
	char	*joined;

	temp = NULL;
	joined = NULL;
	if (*id->i > start)
		temp = ft_strndup(&input[start], *id->i - start);
	if (!id->tokens[*id->j].token_string)
		id->tokens[*id->j].token_string = ft_strjoin(temp, "$");
	else
	{
		joined = id->tokens[*id->j].token_string;
		id->tokens[*id->j].token_string = ft_strjoin(joined, "$");
		free(joined);
	}
	free(temp);
	(*id->i)++;
	(*id->j)++;
}

void	dollar_env(char *input, t_id *id, t_env **env_list)
{
	char	*env_temp;
	char	*joined;

	env_temp = NULL;
	joined = NULL;
	env_temp = environment_variable(input, id->i, env_list);
	if (id->tokens[*id->j].token_string)
	{
		joined = id->tokens[*id->j].token_string;
		id->tokens[*id->j].token_string = ft_strjoin(joined, env_temp);
		free(joined);
	}
	else
		id->tokens[*id->j].token_string = ft_strdup(env_temp);
	free(env_temp);
}

void	dollar_remainder(char *input, t_id *id, int start)
{
	char	*temp;
	char	*joined;

	temp = NULL;
	joined = NULL;
	temp = ft_strndup(&input[start], *id->i - start);
	if (id->tokens[*id->j].token_string)
	{
		joined = id->tokens[*id->j].token_string;
		id->tokens[*id->j].token_string = ft_strjoin(joined, temp);
		free(joined);
		free(temp);
	}
	else
		id->tokens[*id->j].token_string = temp;
}

void	dollar_multiple(char *input, t_id *id, int start)
{
	char	*temp;
	char	*joined;

	temp = NULL;
	joined = NULL;
	temp = ft_strndup(&input[start], *id->i - start);
	if (id->tokens[*id->j].token_string)
	{
		joined = id->tokens[*id->j].token_string;
		id->tokens[*id->j].token_string = ft_strjoin(joined, temp);
		free(joined);
	}
	else
		id->tokens[*id->j].token_string = ft_strdup(temp);
	free(temp);
}
