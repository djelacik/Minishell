/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:02:00 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/27 13:46:21 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(t_data *data)
{
	int		i;
	int		new_line;

	//token[0] is echo
	i = 1;
	new_line = 1;
	if (data->token_count > 1 && ft_strcmp(data->args[i].token_string, "-n") == 0)
	{
		new_line = 0;
		i++; //skip the "-n"
	}
	while (i < data->token_count)
	{
		printf("%s", data->args[i].token_string);
		if (i + 1 < data->token_count) // " " between strings
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	exec_pwd(void)
{
	char	*current_dir;

	current_dir = NULL;
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		printf("%s\n", current_dir);
	}
	else
	{
		perror("getcwd error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	update_pwd(t_env **head)
{
	char	pwd[1024];
	char	*old_pwd;

	old_pwd = ft_getenv("PWD", *head);
	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		if (old_pwd != NULL)
		{
			ft_setenv("OLDPWD", old_pwd, head);
		}
		ft_setenv("PWD", pwd, head);
	}
	else
	{
		perror("getcwd error");
	}
}

void	ft_cd(t_data *data, t_env **head)
{
	char	*path;

	if (data->token_count > 1)
		path = data->args[1].token_string;
	else
	{
		path = ft_getenv("HOME", *head);
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return ;
		}
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
}

void	ft_exit(t_data *data)
{
	if (data->token_count > 1)
	{
		printf("Too many arguments for exit\n");
		return ;
	}
	printf("exit\n");
	exit (0);
}
