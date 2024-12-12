#include "../../includes/minishell.h"

int	process_rest_redir(char *input, t_id *id, int start)
{
	if (input[*id->i] == '<' || input[*id->i] == '>')
	{
		if (*id->i > start)
			process_redir_arg(input, id, start);
		if (input[*id->i] == '<' && input[*id->i + 1] == '<')
			return (process_double_here_doc(input, id));
		if (input[*id->i] == '>' && input[*id->i + 1] == '>')
			return (process_double_append(input, id));
		if (input[*id->i] == '>')
			return (process_output(id));
		if (input[*id->i] == '<')
			return (process_input(id));
	}
	return (1);
}

int	process_rest_pipe(char *input, t_id *id, int start)
{
	if (input[*id->i] == '|')
	{
		if (*id->i > start)
		{
			id->tokens[*id->j].token_string = ft_strndup(&input[start], *id->i - start);
			id->tokens[*id->j].token_type = ARGUMENT;
			id->tokens[*id->j].builtin_type = BUILTIN_NONE;
			(*id->j)++;
		}
		if (input[*id->i] == '|')
		{
			id->tokens[*id->j].token_string = ft_strdup("|");
			id->tokens[*id->j].token_type = PIPE;
			(*id->i)++;
		}
		(*id->j)++;
		start = *id->i;
		return (CONTINUE_PRO);
	}
	return (1);
}

int	process_rest_args(char *input, t_id *id, int start)
{
	char	*seg;
	char	*temp;

	seg = NULL;
	temp = NULL;
	if (*id-> i > start)
	{
		if (id->tokens[*id->j].token_string)
		{
			seg = ft_strndup(&input[start], *id->i - start);
			temp = id->tokens[*id->j].token_string;
			id->tokens[*id->j].token_string = ft_strjoin(temp, seg);
			free(temp);
			free(seg);
		}
		else
			id->tokens[*id->j].token_string = ft_strndup(&input[start], *id->i - start);
	}
	return (1);
}

int	process_rest(char *input, t_id *id, t_env **env_list)
{
	int	start;
	int	result;
	char	*temp;
	char	*env_temp;

	temp = NULL;
	env_temp = NULL;
	start = *id->i;
	while (input[*id->i] && input[*id->i] != ' ' && input[*id->i] != '\'' && input[*id->i] != '"')
	{
		if ((input[*id->i] == '<' || input[*id->i] == '>' || input[*id->i] == '|') && (input[*id->i + 1] == '\0'))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		if (input[*id->i] == '$')
		{
			if (*id->i > start)
			{
				temp = ft_strndup(&input[start], *id->i - start);
			}
			start = *id->i;
			env_temp = environment_variable(input, id->i, env_list);
			if (temp)
			{
				id->tokens[*id->j].token_string = ft_strjoin(temp, env_temp);
				free(temp);
			}
			else
				id->tokens[*id->j].token_string = ft_strdup(env_temp);
			free(env_temp);
			(*id->j)++;
			return (CONTINUE_PRO);
		}
		result = process_rest_redir(input, id, start);
		if (result == CONTINUE_PRO || result == -1)
			return (result);
		result = process_rest_pipe(input, id, start);
		if (result == CONTINUE_PRO || result == -1)
			return (result);
		(*id->i)++;
	}
	return (process_rest_args(input, id, start));
}
