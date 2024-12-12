#include "../../includes/minishell.h"

int	process_redir_arg(char *input, t_id *id, int start)
{
	if (*id->i > start)
	{
		id->tokens[*id->j].token_string = ft_strndup(&input[start], *id->i - start);
		id->tokens[*id->j].token_type = ARGUMENT;
		id->tokens[*id->j].builtin_type = BUILTIN_NONE;
		(*id->j)++;
		start = *id->i;
	}
	return (1);
}

int	process_double_here_doc(char *input, t_id *id)
{
	if (input[*id->i + 2] == '<' || input[*id->i + 2] == '>' || input[*id->i + 2] == '|')
	{
		while (input[*id->i] && (input[*id->i] == '<' || input[*id->i] == '>' || input[*id->i] == '|'))
			(*id->i)++;
		id->tokens[*id->j].token_string = ft_strndup(&input[*id->i - 1], 1);
		printf("syntax error near unexpected token `%s'\n", id->tokens[*id->j].token_string);
		return ( -1);
	}
	id->tokens[*id->j].token_string = ft_strdup("<<");
	id->tokens[*id->j].token_type = REDIR_HERE_DOC;
	(*id->i) += 2;
	(*id->j)++;
	return (CONTINUE_PRO);
}

int	process_double_append(char *input, t_id *id)
{
	if (input[*id->i + 2] == '>' || input[*id->i + 2] == '<' || input[*id->i + 2] == '|')
	{
		while (input[*id->i] && (input[*id->i] == '<' || input[*id->i] == '>' || input[*id->i] == '|'))
			(*id->i)++;
		id->tokens[*id->j].token_string = ft_strndup(&input[*id->i - 1], 1);
		printf("syntax error near unexpected token `%s'\n", id->tokens[*id->j].token_string);
		return (-1);
	}
	id->tokens[*id->j].token_string = ft_strdup(">>");
	id->tokens[*id->j].token_type = REDIR_APPEND;
	(*id->i) += 2;
	(*id->j)++;
	return (CONTINUE_PRO);
}

int process_output(t_id *id)
{
	id->tokens[*id->j].token_string = ft_strdup(">");
	id->tokens[*id->j].token_type = REDIR_OUTPUT;
	(*id->i)++;
	(*id->j)++;
	return (CONTINUE_PRO);
}

int	process_input(t_id *id)
{
	id->tokens[*id->j].token_string = ft_strdup("<");
	id->tokens[*id->j].token_type = REDIR_INPUT;
	(*id->i)++;
	(*id->j)++;
	return (CONTINUE_PRO);
}
