#include "../../includes/minishell.h"

char	*singleq(char *input, int *i)
{
	char	*quoted;

	quoted = single_quotes(input, i);
	if (quoted == NULL)
	{
		printf("syntax error: unexpected EOF while looking for matching `\''\n");
		return (NULL);
	}
	return (quoted);
}

char	*doubleq(char *input, int *i, t_env **env_list)
{
	char	*quoted;

	quoted = double_quotes(input, i, env_list);
	if (quoted == NULL)
	{
		printf("syntax error: unexpected EOF while looking for matching `\"'\n");
		return (NULL);
	}
	return (quoted);
}

int	process_quotes(char *input, t_id *id, t_env **env_list)
{
	char	*quoted;
	char	*r;

	r = NULL;
	if (input[*id->i] == '\'' || input[*id->i] == '"')
	{
		quoted = NULL;
		if (input[*id->i] == '\'')
			quoted = singleq(input, id->i);
		else if (input[*id->i] == '"')
			quoted = doubleq(input, id->i, env_list);
		if (!quoted)
			return (-1);
		if (id->tokens[*id->j].token_string)
		{
			r = id->tokens[*id->j].token_string;
			id->tokens[*id->j].token_string = ft_strjoin(r, quoted);
			free(r);
			free(quoted);
		}
		else
			id->tokens[*id->j].token_string = quoted;
	}
	return (1);
}
