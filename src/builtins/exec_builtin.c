/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:02:00 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/13 12:33:52 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(t_command *command)
{
	int		i;
	int		new_line;

	//token[0] is echo
	i = 1;
	new_line = 1;
	if (command->token_count > 1 && ft_strcmp(command->tokens[i].token_string, "-n") == 0)
	{
		new_line = 0;
		i++; //skip the "-n"
	}
	while (i < command->token_count)
	{
		printf("%s", command->tokens[i].token_string);
		if (i + 1 < command->token_count) // " " between strings
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	exec_pwd(void)
{
	const char	*current_d;
	
	current_d = getenv("PWD");
	printf("%s", current_d);
	return (EXIT_SUCCESS);
}

void	update_pwd(void)
{
	char	pwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = getenv("PWD");
	
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		if (old_pwd != NULL)
		{
			setenv("OLDPWD", old_pwd, 1); // Update OLDPWD
		}
		setenv("PWD", pwd, 1); // Update PWD
	}
	else
	{
		perror("Error updating pwd\n");
	}
}

// if command->tokens[0].token_string == "cd"
void	ft_cd(t_command *command)
{
	char	*path;

	// path = /home/projects/minishell
	if (command->token_count > 1)
		path = command->tokens[1].token_string;
	else
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("HOME not set\n");
			return ;
		}
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	update_pwd();
}

void	ft_exit(t_command *command)
{
	if (command->token_count > 1)
	{
		printf("Too many arguments for exit\n");
		return ;
	}
	printf("exit\n");
	exit (0);
}
