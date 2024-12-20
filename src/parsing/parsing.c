/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:16:28 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:16:57 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	result;

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

static int	token_process_start(char *input, t_id *id, \
		t_tokens *tokens, t_env **env_list)
{
	int	result;

	result = process_token(input, id, env_list);
	if (result == -1)
	{
		free_id_and_tokens(id, tokens, *id->j);
		return (-1);
	}
	if (result == CONTINUE_PRO)
		return (CONTINUE_PRO);
	if (!tokens[*id->j].token_string)
	{
		free_id_and_tokens(id, tokens, *id->j);
		return (-1);
	}
	assign_type(input, tokens, id->j, id->i);
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
		result = token_process_start(input, &id, tokens, env_list);
		if (result == -1)
			return (NULL);
		if (result == CONTINUE_PRO)
			continue ;
	}
	tokens[*id.j].token_string = NULL;
	free_id(&id);
	return (tokens);
}
