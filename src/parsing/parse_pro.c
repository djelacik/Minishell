#include "../../includes/minishell.h"

int	process_start(char *input, t_id *id)
{
	int	start;

	if (input[0] == '|' || (input[*id->i] == '|' && *id->j == 0))
	{
		printf("syntax error near unexpected token `|'\n");
		return (-1);
	}
	if (input[0] == '/' && (input[*id->i] == '/' && *id->j == 0))
	{
		start = *id->i;
		while (input[*id->i] && input[*id->i] != ' ' && input[*id->i] != '\'' && input[*id->i] != '"')
			(*id->i)++;
		id->tokens[*id->j].token_string = ft_strndup(&input[start], *id->i - start);
		id->tokens[*id->j].token_type = COMMAND;
		id->tokens[*id->j].builtin_type = BUILTIN_NONE;
		(*id->j)++;
		return (CONTINUE_PRO);
	}
	return (1);
}

int	process_redirs(char *input, t_id *id)
{
	if (input[*id->i] == '>' || input[*id->i] == '<')
	{
		id->tokens[*id->j].token_string = redir_symb(input, id->i, &id->tokens[*id->j]);
		if (id->tokens[*id->j].token_string == NULL)
		{
			printf("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		if (id->tokens[*id->j].token_type == EMPTY)
		{
			printf("syntax error near unexpected token `%s'\n", id->tokens[*id->j].token_string);
			return (-1);
		}
		(*id->j)++;
		return (CONTINUE_PRO);
	}
	return (1);
}

int	process_pipe(char *input, t_id *id)
{
	int	k;

	if (input[*id->i] == '|')
	{
		k = *id->i + 1;
		while (input[k] == ' ')
			k++;
		if (input[k] == '|')
		{
			printf("syntax error near unexpected token `|'\n");
			return (-1);
		}
		if (input[k] == '\0')
		{
			printf("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		id->tokens[*id->j].token_string = handle_pipes(input, id->i, &id->tokens[*id->j]);
		(*id->j)++;
		return (CONTINUE_PRO);
	}
	return (1);
}

int	process_dollar(char *input, t_id *id, t_env **env_list)
{
	char	*env_temp;
	char	*temp;
	int		start;

	env_temp = NULL;
	temp = NULL;
	if (input[*id->i] == '$')
	{
		id->tokens[*id->j].token_string = environment_variable(input, id->i, env_list);
		if (id->tokens[*id->j].token_string && id->tokens[*id->j].token_string[0] == '\0')
		{
			if (input[*id->i] == '\0' && *id->j == 0)
			{
				printf("");
				return (-1);
			}
		}
		if (input[*id->i] == '=' || input[*id->i] == '.')
		{
			env_temp = id->tokens[*id->j].token_string;
			start = *id->i;
			while (input[*id->i] && input[*id->i] != ' ' && input[*id->i] != '\'' && input[*id->i] != '"')
				(*id->i)++;
			temp = ft_strndup(&input[start], *id->i - start);
			id->tokens[*id->j].token_string = ft_strjoin(env_temp, temp);
			free(temp);
			free(env_temp);
		}
	}
	return (1);
}
