/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:02:00 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/03 12:20:02 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(char **args)
{
	int		i;
	int		new_line;

	i = 2;
	new_line = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	exec_pwd()
{
	const char	*current_d;
	
	current_d = getenv("PWD");
	printf("%s", current_d);
	return (EXIT_SUCCESS);
}
