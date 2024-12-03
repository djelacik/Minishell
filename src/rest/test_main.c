/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/03 15:40:22 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data)
		return ;
	while (i < data->cmnd_count)
	{
		if (data[i].args)
		{
			j = 0;
			while (data[i].args[j].token_string)
			{
				free(data[i].args[j].token_string);
				j++;
			}
			free(data[i].args);
		}
		i++;
	}
	free(data);
}

static void	free_tokens(t_tokens *tokens)
{
	int	i;

	i = 0;
	while(tokens[i].token_string)
	{
		free(tokens[i].token_string);
		i++;
	}
	free(tokens);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_cmnds		cmnds;
	char		*input;
	t_tokens	*tokens;
	t_data		*data;

	//temp lines for manual initilazion
	ft_bzero(&cmnds, sizeof(t_cmnds));
	init_list(&cmnds.env_list, env);	
	// ------------------------------ //

	while (1)
	{
		input = readline("minishell >>> ");
		if (!input) // when user exit with Ctrl+D, readline returns NULL
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		tokens = tokenize_input(input, &cmnds.env_list);
		if (tokens)
		{
			//print_tokens(tokens);
			data = init_data(tokens);
			if (data)
			{
				cmnds.data = data;
				print_cmnds(&cmnds);
				cmnds.command_count = cmnds.data->cmnd_count;
				start_process(&cmnds);
				free_data(data);
			}
			free_tokens(tokens);
		}
		free(input);
	}
	return(0);
}
