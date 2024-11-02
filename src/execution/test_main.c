/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/02 19:34:20 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//This will go to parsing
t_builtin	builtin_type(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (BUILTIN_ECHO);
	else if (ft_strcmp(command, "cd") == 0)
		return (BUILTIN_CD);
	else if (ft_strcmp(command, "pwd") == 0)
		return (BUILTIN_PWD);
	else if (ft_strcmp(command, "export") == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strcmp(command, "unset") == 0)
		return (BUILTIN_UNSET);
	else if (ft_strcmp(command, "env") == 0)
		return (BUILTIN_ENV);
	else if (ft_strcmp(command, "exit") == 0)
		return (BUILTIN_EXIT);
	return (BUILTIN_NONE);	
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[1], "echo") == 0)
		execute_echo(argv);
	return (EXIT_SUCCESS);
}
