#include "../../includes/minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return 0;
	if (ft_strcmp(command, "echo") == 0)
		return 1;
	if (ft_strcmp(command, "cd") == 0)
		return 1;
	if (ft_strcmp(command, "pwd") == 0)
		return 1;
	if (ft_strcmp(command, "export") == 0)
		return 1;
	if (ft_strcmp(command, "unset") == 0)
		return 1;
	if (ft_strcmp(command, "env") == 0)
		return 1;
	if (ft_strcmp(command, "exit") == 0)
		return 1;
	return 0;
}

void	execute_builtin(t_data *data, t_cmnds *cmnds)
{
	if (ft_strcmp(data->args[0].token_string, "echo") == 0)
		exec_echo(data);
	else if (ft_strcmp(data->args[0].token_string, "cd") == 0)
		ft_cd(data, &cmnds->env_list);
	else if (ft_strcmp(data->args[0].token_string, "pwd") == 0)
		exec_pwd();
	else if (data->args[1].token_string && 
				(ft_strcmp(data->args[0].token_string, "export") == 0))
			export_add(&cmnds->env_list, data);
	else if (ft_strcmp(data->args[0].token_string, "export") == 0)
		export_print(cmnds->env_list);
	else if (ft_strcmp(data->args[0].token_string, "unset") == 0)
		ft_unset(&cmnds->env_list, data);
	else if (ft_strcmp(data->args[0].token_string, "env") == 0)
		ft_env(cmnds->env_list);
	else if (ft_strcmp(data->args[0].token_string, "exit") == 0)
		ft_exit(data);
	else
	{
		printf("minishell: command not found: %s\n", data->args[0].token_string);
		error_exit(cmnds, NULL, EXIT_FAILURE);
	}
	update_env_cpy(cmnds);
}
