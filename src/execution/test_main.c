/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/25 13:32:04 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_arr(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*head;
	t_data		*data;
	
	data = malloc(sizeof(t_data));
	data->token_count = 3;
	data->args = malloc(sizeof(t_tokens) * data->token_count);
	data->args[1].token_string = ft_strdup("TEST1");
	data->args[2].token_string = ft_strdup("TEST2=");
	data->args[3].token_string = ft_strdup("TEST3=3");
	
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
	export_add(&head, data);
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
