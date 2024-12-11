/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:02:00 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/05 15:43:37 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(t_data *data)
{
	int		i;
	int		new_line;

	//token[0] is echo
	dbg_print("Executing echo command\n");
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
		i++;
	}
	if (new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	exec_pwd(void)
{
	char	current_dir[1024];

	dbg_print("Executing pwd command\n");
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		dbg_print("Current directory: %s\n", current_dir);
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
	char	*pwd;
	char	*old_pwd;

	dbg_print("Updating PWD and OLDPWD environment variables\n");
	old_pwd = ft_getenv("PWD", *head);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd error");
		return ;
	}
	if (old_pwd != NULL)
	{
		dbg_print("Setting OLDPWD: %s\n", old_pwd);
		ft_setenv("OLDPWD", old_pwd, head);
	}
	dbg_print("Setting PWD: %s\n", pwd);
	ft_setenv("PWD", pwd, head);
	free(pwd);
}

void	ft_cd(t_data *data, t_env **head)
{
	char	*path;

	dbg_print("Executing cd command\n");
	if (data->token_count > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
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
	dbg_print("Changing directory to: %s\n", path);
	if (chdir(path) != 0)
	{
		perror("cd");
		return ;
	}
	update_pwd(head);
}

void	ft_exit(t_data *data)
{
	dbg_print("Executing exit command\n");
	if (data->token_count > 1)
	{
		printf("Too many arguments for exit\n");
		return ;
	}
	printf("exit\n");
	exit (0);
}
