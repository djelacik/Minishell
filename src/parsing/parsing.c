#include "../../includes/minishell.h"

static void	assign_type(char *input, t_tokens *tokens, int *j, int *i)
{
	if (!tokens || !tokens[*j].token_string)
		return ;
	if (*j == 0 || ft_strcmp(tokens[*j - 1].token_string, "|") == 0)
	{
		tokens[*j].token_type = COMMAND;
		tokens[*j].builtin_type = builtin_type(tokens[*j].token_string);
	}
	else if (ft_strcmp(tokens[*j - 1].token_string, "<") == 0)
		tokens[*j].token_type = REDIR_INPUT;
	else if (ft_strcmp(tokens[*j - 1].token_string, ">") == 0)
		tokens[*j].token_type = REDIR_OUTPUT;
	else if (ft_strcmp(tokens[*j - 1].token_string, ">>") == 0)
		tokens[*j].token_type = REDIR_APPEND;
	else if (ft_strcmp(tokens[*j - 1].token_string, "<<") == 0)
		tokens[*j].token_type = REDIR_HERE_DOC;
	else if (tokens[*j].token_type == 0)
	{
		tokens[*j].token_type = ARGUMENT;
		tokens[*j].token_type = BUILTIN_NONE;
	}
	if (input[*i] == ' ' || input[*i] == '\0')
		(*j)++;
}

static int	process_token(char *input, t_id *id, t_env **env_list)
{
	int result;

	result = process_start(input, id);
	if (result == -1 || result == CONTINUE_PRO)
		return (result);
	result = process_redirs(input, id);
	if (result == -1 || result == CONTINUE_PRO)
		return (result);
	result = process_pipe(input, id);
	if (result == -1 || result == CONTINUE_PRO)
		return (result);
	if (process_quotes(input, id, env_list) == -1)
		return (-1);
	if (process_dollar(input, id, env_list) == -1)
		return (-1);
	result = process_rest(input, id, env_list);
	if (result == -1 || result == CONTINUE_PRO)
		return (result);
	return (0);
}

t_tokens	*tokenize_input(char *input, t_env **env_list)
{
	t_tokens	*tokens;
	t_id		id;
	int			result;

	if (init_id_and_tokens(&id, &tokens, input, env_list) == -1)
		return (NULL);
	while (input[*id.i])
	{
		while (input[*id.i] == ' ' || input[*id.i] == '\t')
			(*id.i)++;
		if (!input[*id.i])
			break ;
		result = process_token(input, &id, env_list);
		if (result == -1)
		{
			free_id_and_tokens(&id, tokens, *id.j);
			return (NULL);
		}
		if (result == CONTINUE_PRO)
			continue ;
		if (!tokens[*id.j].token_string)
		{
			free_id_and_tokens(&id, tokens, *id.j);
			return (NULL);
		}
		assign_type(input, tokens, id.j, id.i);
	}
	tokens[*id.j].token_string = NULL;
	free_id(&id);
	return (tokens);
}

/*t_tokens	*tokenize_input(char *input, t_env **env_list)
{
	t_tokens	*tokens;
	int		token_count;
	int		i;
	int		j;
	int		k;
	int		start;

	token_count = count_tokens(input, env_list);
	tokens = malloc((token_count + 1) * sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < token_count + 1)
	{
		tokens[i].token_string = NULL;
		i++;
	}
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[0] == '|' || (input[i] == '|' && j == 0))
		{
			printf("syntax error near unexpected token `|'\n");
			free_exist_tokens(tokens, j);
			return (NULL);
		}
		if (!input[i])
			break;
		if (input[0] == '/' && (input[i] == '/' && j == 0))
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"')
				i++;
			tokens[j].token_string = ft_strndup(&input[start], i - start);
			tokens[j].token_type = COMMAND;
			tokens[j].builtin_type = BUILTIN_NONE;
			j++;
			continue ;
		}
		else if (input[i] == '>' || input[i] == '<')
		{
			tokens[j].token_string = redir_symb(input, &i, &tokens[j]);
			if (tokens[j].token_string == NULL)
			{
				printf("syntax error near unexpected token `newline'\n");
				free_exist_tokens(tokens, j);
				return (NULL);
			}
			if (tokens[j].token_type == EMPTY)
			{
				printf("syntax error near unexpected token `%s'\n", tokens[j].token_string);
				free_exist_tokens(tokens, j);
				return (NULL);
			}
			j++;
			continue ;
		}
		else if (input[i] == '|')
		{
			k = i + 1;
			while (input[k] == ' ')
				k++;
			if (input[k] == '|')
			{
				printf("syntax error near unexpected token `|'\n");
				free_exist_tokens(tokens, j);
				return (NULL);
			}
			if (input[k] == '\0')
			{
				printf("syntax error near unexpected token `newline'\n");
				free_exist_tokens(tokens, j);
				return (NULL);
			}
			tokens[j].token_string = handle_pipes(input, &i, &tokens[j]);
			j++;
			continue ;
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			char *quoted = NULL;
			if (input[i] == '\'')
			{
				quoted = single_quotes(input, &i);
				//tokens[j].token_string = single_quotes(input, &i);
				if (tokens[j].token_string == NULL quoted == NULL)
				{
					printf("syntax error: unexpected EOF while looking for matching `\''\n");
					free_exist_tokens(tokens, j);
					return (NULL);
				}
			}
			else if (input[i] == '"')
			{
				if (calculate_quotes_double(input) == 0)
				{
					printf("syntax error: unexpected EOF while looking for matching `\"'\n");
					free_exist_tokens(tokens, j);
					return (NULL);
				}
				while (input[i] && input[i] == '"' && (input[i + 1] == '"' || input[i + 1] != ' '))
					i++;
				//tokens[j].token_string = double_quotes(input, &i, env_list);
				quoted = double_quotes(input, &i, env_list);
				if (tokens[j].token_string == NULL quoted == NULL)
				{
					printf("syntax error: unexpected EOF while looking for matching `\"'\n");
					free_exist_tokens(tokens, j);
					return (NULL);
				}
			}
			if (tokens[j].token_string)
			{
				char *a = tokens[j].token_string;
				tokens[j].token_string = ft_strjoin(a, quoted);
				free(a);
				free(quoted);
			}
			else
				tokens[j].token_string = quoted;

		}
		else if (input[i] == '$')
		{
			tokens[j].token_string = environment_variable(input, &i, env_list);
			if (input[i] == '=' || input[i] == '.')
			{
				char *env_temp = tokens[j].token_string;
				char *temp;
				start = i;
				while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"')
					i++;
				temp = ft_strndup(&input[start], i - start);
				tokens[j].token_string = ft_strjoin(env_temp, temp);
				free(temp);
				free(env_temp);
			}
		}
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"')
			{
				if ((input[i] == '<' || input[i] == '>' || input[i] == '|') && (input[i + 1] == '\0'))
				{
					printf("syntax error near unexpected token `newline'\n");
					free_exist_tokens(tokens, j);
					return (NULL);
				}
				if (input[i] == '<' || input[i] == '>')
				{
					if (i > start)
					{
						tokens[j].token_string = ft_strndup(&input[start], i - start);
						tokens[j].token_type = ARGUMENT;
						tokens[j].builtin_type = BUILTIN_NONE;
						j++;
					}
					if (input[i] == '<' && input[i + 1] == '<')
					{
						if (input[i + 2] == '<' || input[i + 2] == '>' || input[i + 2] == '|')
						{
							while (input[i] && (input[i] == '<' || input[i] == '>' || input[i] == '|'))
								i++;
							tokens[j].token_string = ft_strndup(&input[i - 1], 1);
							printf("syntax error near unexpected token `%s'\n", tokens[j].token_string);
							free_exist_tokens(tokens, j);
							return (NULL);
						}
						tokens[j].token_string = ft_strdup("<<");
						tokens[j].token_type = REDIR_HERE_DOC;
						i += 2;
					}
					else if (input[i] == '>' && input[i + 1] == '>')
					{
						if (input[i + 2] == '>' || input[i + 2] == '<' || input[i + 2] == '|')
						{
							while (input[i] && (input[i] == '<' || input[i] == '>' || input[i] == '|'))
								i++;
							tokens[j].token_string = ft_strndup(&input[i - 1], 1);
							printf("syntax error near unexpected token `%s'\n", tokens[j].token_string);
							free_exist_tokens(tokens, j);
							return (NULL);
						}
						tokens[j].token_string = ft_strdup(">>");
						tokens[j].token_type = REDIR_APPEND;
						i += 2;
					}
					else if (input[i] == '>')
					{
						tokens[j].token_string = ft_strdup(">");
						tokens[j].token_type = REDIR_OUTPUT;
						i++;
					}
					else if (input[i] == '<')
					{
						tokens[j].token_string = ft_strdup("<");
						tokens[j].token_type = REDIR_INPUT;
						i++;
					}
					j++;
					start = i;
					continue ;
				}
				if (input[i] == '|')
				{
					if (i > start)
					{
						tokens[j].token_string = ft_strndup(&input[start], i - start);
						tokens[j].token_type = ARGUMENT;
						tokens[j].builtin_type = BUILTIN_NONE;
						j++;
					}
					if (input[i] == '|')
					{
						tokens[j].token_string = ft_strdup("|");
						tokens[j].token_type = PIPE;
						i++;
					}
					j++;
					start = i;
					continue ;
				}
				i++;
			}
			if (i > start)
			{
				if (tokens[j].token_string)
				{
					char *seg;
					char *tem;
					seg = ft_strndup(&input[start], i - start);
					tem = tokens[j].token_string;
					tokens[j].token_string = ft_strjoin(tem, seg);
					free(tem);
					free(seg);
				}
				else
				{
					tokens[j].token_string = ft_strndup(&input[start], i - start);
				}
				//tokens[j].token_string = ft_strndup(&input[start], i - start);
			}
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
		if (j == 0 || ft_strcmp(tokens[j - 1].token_string, "|") == 0)
		{
			tokens[j].token_type = COMMAND;
			tokens[j].builtin_type = builtin_type(tokens[j].token_string);
		}
		else if (ft_strcmp(tokens[j - 1].token_string, "<") == 0)
			tokens[j].token_type = REDIR_INPUT;
		else if (ft_strcmp(tokens[j - 1].token_string, ">") == 0)
			tokens[j].token_type = REDIR_OUTPUT;
		else if (ft_strcmp(tokens[j - 1].token_string, ">>") == 0)
			tokens[j].token_type = REDIR_APPEND;
		else if (ft_strcmp(tokens[j - 1].token_string, "<<") == 0)
			tokens[j].token_type = REDIR_HERE_DOC;
		else if (tokens[j].token_type == 0)
		{
			tokens[j].token_type = ARGUMENT;
			tokens[j].builtin_type = BUILTIN_NONE;
		}
		if (input[i] == ' ' || input[i] == '\0')
			j++;
		//j++;
	}
	tokens[j].token_string = NULL;
	return (tokens);
}*/
