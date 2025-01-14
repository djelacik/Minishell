/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:02:51 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:06:44 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_input_redir(char *input, int *index, t_tokens *tokens)
{
	char	*symbol;
	int		k;

	k = (*index) + 1;
	while (input[k] == ' ')
		k++;
	if (input[k] == '\0')
		return (NULL);
	if (input[k] == '<' || input[k] == '>' || input[k] == '|')
	{
		if (input[k + 1] == '<' || input[k + 1] == '>')
		{
			symbol = ft_strndup(&input[k], 2);
		}
		else
			symbol = ft_strndup(&input[k], 1);
		tokens->token_type = EMPTY;
	}
	else
	{
		tokens->token_type = REDIR_INPUT;
		symbol = ft_strndup("<", 1);
	}
	(*index)++;
	return (symbol);
}

static char	*handle_here_doc(char *input, int *index, t_tokens *tokens)
{
	char	*symbol;
	int		k;

	k = (*index) + 2;
	while (input[k] == ' ')
		k++;
	if (input[k] == '\0')
		return (NULL);
	if (input[k] == '<' || input[k] == '>' || input[k] == '|')
	{
		if (input[k + 1] == '<' || input[k + 1] == '>')
		{
			symbol = ft_strndup(&input[k], 2);
		}
		else
			symbol = ft_strndup(&input[k], 1);
		tokens->token_type = EMPTY;
	}
	else
	{
		tokens->token_type = REDIR_HERE_DOC;
		symbol = ft_strndup("<<", 2);
	}
	(*index) += 2;
	return (symbol);
}

static char	*handle_output_redir(char *input, int *index, t_tokens *tokens)
{
	char	*symbol;
	int		k;

	k = (*index) + 1;
	while (input[k] == ' ')
		k++;
	if (input[k] == '\0')
		return (NULL);
	if (input[k] == '<' || input[k] == '>' || input[k] == '|')
	{
		if (input[k + 1] == '<' || input[k + 1] == '>')
		{
			symbol = ft_strndup(&input[k], 2);
		}
		else
			symbol = ft_strndup(&input[k], 1);
		tokens->token_type = EMPTY;
	}
	else
	{
		tokens->token_type = REDIR_OUTPUT;
		symbol = ft_strndup(">", 1);
	}
	(*index)++;
	return (symbol);
}

static char	*handle_append_redir(char *input, int *index, t_tokens *tokens)
{
	char	*symbol;
	int		k;

	k = (*index) + 2;
	while (input[k] == ' ')
		k++;
	if (input[k] == '\0')
		return (NULL);
	if (input[k] == '<' || input[k] == '>' || input[k] == '|')
	{
		if (input[k + 1] == '<' || input[k + 1] == '>')
		{
			symbol = ft_strndup(&input[k], 2);
		}
		else
			symbol = ft_strndup(&input[k], 1);
		tokens->token_type = EMPTY;
	}
	else
	{
		tokens->token_type = REDIR_APPEND;
		symbol = ft_strndup(">>", 2);
	}
	(*index) += 2;
	return (symbol);
}

char	*redir_symb(char *input, int *index, t_tokens *tokens)
{
	if (input[*index] == '<' && input[*index + 1] != '<')
		return (handle_input_redir(input, index, tokens));
	else if (input[*index] == '<' && input[*index + 1] == '<')
		return (handle_here_doc(input, index, tokens));
	else if (input[*index] == '>' && input[*index + 1] != '>')
		return (handle_output_redir(input, index, tokens));
	else if (input[*index] == '>' && input[*index + 1] == '>')
		return (handle_append_redir(input, index, tokens));
	return (0);
}
