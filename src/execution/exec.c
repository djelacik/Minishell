#include "../../includes/minishell.h"

static char	*join_cmd_path(char *dir, char *cmd)
{
	char	*single_path;
	char	*full_path;

	single_path = ft_strjoin(dir, "/");
	if (!single_path)
		return (NULL);
	full_path = ft_strjoin(single_path, cmd);
	free(single_path);
	return (full_path);
}

void	*find_path(char *command, t_cmnds *cmnds)
{
	char	*path_value;
	char	*full_path;
	char	**paths;
	int		i;

	path_value = ft_getenv("PATH", cmnds->env_list);
	if (!path_value)
		return (NULL);
	paths = ft_split((const char *)path_value, ':');
	i = 0;
	while (paths[i])
	{
		full_path = join_cmd_path(paths[i], command);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			g_exit_status = 0;
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

static char	**tokens_to_argv(t_tokens *tokens, int token_count)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (token_count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		argv[i] = ft_strdup(tokens[i].token_string);
		if (!argv[i])
		{
			perror(STRDUP_ERR);
			while (i-- < 0)
				free(argv[i]);
			free(argv);
			return (NULL);;
		}
		i++;
	}
	argv[token_count] = NULL;
	return (argv);
}

void	execute_external(t_data *data, t_cmnds *cmnds)
{
	char	*cmd_path;
	char	**argv;

	dbg_print("Executing external command: %s\n", data->args[0].token_string);

	if (ft_strchr(data->args[0].token_string, '/'))
		cmd_path = ft_strdup(data->args[0].token_string);
	else
		cmd_path = find_path(data->args[0].token_string, cmnds);
	if (!cmd_path)
	{
		printf("minishell: command not found: %s\n", data->args[0].token_string);
		g_exit_status = 127;
		error_exit(cmnds, NULL, EXIT_FAILURE);
	}
	argv = tokens_to_argv(data->args, data->token_count);
	if (!argv)
		error_exit(cmnds, NULL, EXIT_FAILURE);
	dbg_print("Command path: %s\n", cmd_path);
	for (int i = 0; argv[i]; i++)
		dbg_print("Arg[%d]: %s\n", i, argv[i]);
	execve(cmd_path, argv, cmnds->env_cpy);
	perror(EXEC_ERR);
	free(cmd_path);
	free_array(argv);
	error_exit(cmnds, NULL, EXIT_FAILURE);
}
