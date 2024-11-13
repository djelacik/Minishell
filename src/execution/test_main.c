/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/13 12:17:59 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env		*head;
	t_command	*command;
	
	command = malloc(sizeof(t_command));
	command->token_count = 3;
	command->tokens = malloc(sizeof(t_tokens) * command->token_count);
	command->tokens[0].token_string = ft_strdup("TEST1");
	command->tokens[1].token_string = ft_strdup("TEST2=");
	command->tokens[2].token_string = ft_strdup("TEST3=3");
	
	if (argc < 2)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[1], "echo") == 0)
		exec_echo(argv);
	if (ft_strcmp(argv[1], "pwd") == 0)
		exec_pwd();
	init_list(&head, envp);
	if (ft_strcmp(argv[1], "unset") == 0)
	{
		ft_unset(&head, argv[2]);
		ft_env(head);
	}
	export_add(&head, command);
	if (ft_strcmp(argv[1], "export") == 0)
	{
		export_print(head);
	}
	if (ft_strcmp(argv[1], "env") == 0)
	{
		ft_env(head);
	}
	return (EXIT_SUCCESS);
}
