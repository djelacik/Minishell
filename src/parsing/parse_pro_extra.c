/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pro_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:14:13 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:14:56 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_d(char *input, t_id *id, int start)
{
	char	*env_temp;

	env_temp = NULL;
	if (*id->i > start)
	{
		env_temp = ft_strndup(&input[start], *id->i - start);
		id->tokens[*id->j].token_string = ft_strjoin(env_temp, "$");
		free(env_temp);
	}
	else
		id->tokens[*id->j].token_string = ft_strdup("$");
	(*id->i)++;
	return (1);
}

void	process_if_count(char *input, t_id *id, int start, t_env **env_list)
{
	char	*env_temp;

	env_temp = NULL;
	env_temp = ft_strndup(&input[start], *id->i - start);
	id->tokens[*id->j].token_string = ft_strjoin(env_temp, \
			environment_variable(input, id->i, env_list));
}

int	process_d_count(char *input, t_id *id)
{
	int	count;

	count = 0;
	while (input[*id->i] == '$' && input[*id->i + 1] == '$')
	{
		(*id->i)++;
		count++;
	}
	return (count);
}

int	process_end_spes(char *input, t_id *id)
{
	char	*env_temp;

	env_temp = NULL;
	if (id->tokens[*id->j].token_string && \
			id->tokens[*id->j].token_string[0] == '\0')
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
		process_dollar_join(input, id, id->i, env_temp);
	}
	return (1);
}
