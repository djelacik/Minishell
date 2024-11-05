/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:23:55 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/05 15:09:35 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//This will go to parsing
/* static t_builtin	builtin_type(char *command)
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
} */

static t_command	*init_command(t_tokens *token)
{
	t_command	*command;
	int			i;
	int			count;

	command = malloc(sizeof(t_command));
	i = 0;
	count = 0;
	while(token[i].token_string)
	{
		if (token[i].token_string)
		{
			printf("Token string: %s, toke typen: %d, in index %d\n", token[i].token_string, token[i].token_type, i);
		}

		count++;
		i++;
	}
	command->token_count = count;
	return (command);
}

/* int main(int argc, char **argv)
{
	if (argc < 2)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[1], "echo") == 0)
		exec_echo(argv);
	if (ft_strcmp(argv[1], "pwd") == 0)
		exec_pwd(argv[1]);
	return (EXIT_SUCCESS);
}
 */


static void	print_tokens(t_tokens *tokens)
{
	int i;

	i = 0;
	while (tokens[i].token_string)
	{
		printf("%s ", tokens[i].token_string);
		if (tokens[i].token_type == COMMAND)
			printf("%d\n", tokens[i].token_type);
		else if (tokens[i].token_type == ARGUMENT)
			printf("%d\n", tokens[i].token_type);
		i++;
	}
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*input;
	t_tokens *tokens;
	t_command	*command;
	int i;

	while (1)
	{
		input = readline("minishell % ");
		if (!input) // when user exit with Ctrl+D, readline returns NULL
			break ;
		add_history(input);
		tokens = tokenize_input(input);
		i = 0;
		if (tokens)
		{
			command = init_command(tokens, 4);
			print_tokens(tokens);
			//start_process(command);
			while (tokens[i].token_string)
				free(tokens[i++].token_string);
			free(tokens);
		}
		free(input);
	}
	return(0);
}
