/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:02:00 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/19 10:50:16 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(t_data *data)
{
	int		i;
	int		new_line;

	dbg_print("Executing echo command\n");
	i = 1;
	new_line = 1;
	if (data->token_count > 1 && ft_strcmp(data->args[i].token_string, "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (i < data->token_count)
	{
		printf("%s", data->args[i].token_string);
		if (i + 1 < data->token_count)
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	g_exit_status = 0;
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
	g_exit_status = 0;
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
		g_exit_status = 1;
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
		g_exit_status = 1;
		return ;
	}
	update_pwd(head);
	g_exit_status = 0;
}

void	ft_exit(t_data *data, t_cmnds *cmnds)
{
	int		exit_num;

	exit_num = 0;
	dbg_print("Executing exit command\n");
	printf("exit\n");
	if (data->token_count > 2 && ft_isdigit(data->args[1].token_string) == 1)
	{
		printf("exit: too many arguments\n");
		g_exit_status = ft_atoi("1");
		return ;
	}
	if (data->args[1].token_string)
	{	
		if (ft_isdigit(data->args[1].token_string) == 0)
		{
			printf("exit: %s: numeric argument required\n", data->args[1].token_string);
			exit_num = ft_atoi("2");
		}
		else
		{
			exit_num = ft_atoi(data->args[1].token_string);
			exit_num = exit_num % 256;
		}
	}
	//g_exit_status = exit_num;
	error_exit(cmnds, NULL, exit_num);
}

