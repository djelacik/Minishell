/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:02:00 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/10 15:56:21 by djelacik         ###   ########.fr       */
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
