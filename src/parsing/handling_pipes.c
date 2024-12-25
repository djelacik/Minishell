/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:02:19 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:02:40 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_pipes(char *input, int *index, t_tokens *tokens)
{
	char	*pipe;

	pipe = NULL;
	if (input[*index] == '|')
	{
		tokens->token_type = PIPE;
		pipe = ft_strndup("|", 1);
		(*index)++;
	}
	return (pipe);
}
