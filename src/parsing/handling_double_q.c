/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_double_q.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:00:42 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:01:22 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	extract_double_content(char *input, int *index, \
		char *quoted_input, t_env **env_list)
{
	char	*env_var;
	int		i;

	i = 0;
	while (input[*index] && input[*index] != '"')
	{
		if (input[*index] == '$')
		{
			env_var = environment_variable(input, index, env_list);
			if (env_var)
			{
				append_env(quoted_input, &i, env_var);
				free(env_var);
				continue ;
			}
		}
		else
		{
			quoted_input[i++] = input[*index];
			(*index)++;
		}
	}
	quoted_input[i] = '\0';
}

static char	*extract_double_input(char *input, int *index, t_env **env_list)
{
	char	*quoted_input;
	int		quoted_len;

	quoted_len = calculate_double_len(input, *index, '"', env_list);
	quoted_input = malloc((quoted_len + 1) * sizeof(char));
	if (!quoted_input)
		return (NULL);
	if (input[*index] && input[*index] == '"')
		(*index)++;
	extract_double_content(input, index, quoted_input, env_list);
	return (quoted_input);
}

int	calculate_quotes_double(char *input)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (input[i])
	{
		if (input[i] == '"')
			quote_count++;
		i++;
	}
	if (quote_count % 2 != 0)
		return (0);
	return (1);
}

int	calculate_double_len(char *input, int start_index, \
		char quote_type, t_env **env_list)
{
	char	*env_var;
	int		len;
	int		i;

	len = 0;
	i = start_index;
	while (input[i] && input[i] == quote_type)
		i++;
	while (input[i] && input[i] != quote_type)
	{
		if (input[i] == '$')
		{
			env_var = environment_variable(input, &i, env_list);
			if (env_var)
			{
				len += ft_strlen(env_var);
				free(env_var);
			}
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*double_quotes(char *input, int *index, t_env **env_list)
{
	char	*quoted_input;
	char	*parsed;

	if (calculate_quotes_double(input) == 0)
		return (NULL);
	parsed = NULL;
	quoted_input = extract_double_input(input, index, env_list);
	if (!quoted_input)
		return (NULL);
	parsed = ft_strdup(quoted_input);
	free(quoted_input);
	if (input[*index] == '"')
		(*index)++;
	return (parsed);
}
