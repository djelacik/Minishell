/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/25 18:57:39 by djelacik         ###   ########.fr       */
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

void	init_data(t_data *data)
{
	//allocate memory for t_tokens;
	//allocate memory for t_redirect;
	//rest of your functions for saving info
}

void	init_structs(t_cmnds *commands, int cmd_count, char **envp)
{
	int		i;
	
	commands->data = malloc(sizeof(t_data) * cmd_count);
	if (!commands->data)
	{
		perror(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
	init_list(&commands->env_list, envp);
	commands->command_count = cmd_count;
	i = 0;
	while (i < cmd_count)
	{
		init_data(&commands->data[i]);
		i++;
	}
	//rest of your functions
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_cmnds		cmnds;
	int			cmd_count;
	
	cmd_count = calculate_cmd_count();
	init_structs(&cmnds, cmd_count, envp);
	while (1)
	{
		input = readline("minishell % ");
		if (!input) // when user exit with Ctrl+D, readline returns NULL
			break ;
		add_history(input);
		save_info(input);//we should save everything trough one function
		execution(&cmnds);
		free(input);
	}
	return(0);
}
