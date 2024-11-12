/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/12 21:02:56 by djelacik         ###   ########.fr       */
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
	command->tokens[0].token_string = ft_strdup("TEST=");
	command->tokens[1].token_string = ft_strdup("TEST=2");
	command->tokens[2].token_string = ft_strdup("TEST=3");
	
	if (argc < 2)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[1], "echo") == 0)
		exec_echo(argv);
	if (ft_strcmp(argv[1], "pwd") == 0)
		exec_pwd();
	init_list(&head, envp);
	//ft_env(head);
	if (ft_strcmp(argv[1], "unset") == 0)
	{
		ft_unset(&head, argv[2]);
		ft_env(head);
	}
	if (ft_strcmp(argv[1], "export") == 0)
	{
		export_add(&head, command);
	}
	ft_env(head);
	return (EXIT_SUCCESS);
}
