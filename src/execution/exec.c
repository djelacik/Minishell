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
	{
		perror(MALLOC_ERR);
		exit(EXIT_FAILURE);
	}
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
			exit(EXIT_FAILURE);
		}
		i++;
	}
	argv[token_count] = NULL;
	return (argv);
}
void	execute_command(t_data *data, t_cmnds *cmnds)
{
	char	*cmd_path;
	char	**argv;

	if (is_builtin(data->args[0].token_string))
	{
		execute_builtin(data, cmnds);
		exit(EXIT_SUCCESS);
	}
	cmd_path = find_path(data->args[0].token_string, cmnds);
	if (!cmd_path)
	{
		fprintf(stderr, "minishell: command not found: %s\n", data->args[0].token_string);
		exit(EXIT_FAILURE);
	}
	argv = tokens_to_argv(data->args, data->token_count);
	execve(cmd_path, argv, cmnds->env_cpy);
	perror(EXEC_ERR);
	free(cmd_path);
	free_array(argv);
	exit(EXIT_FAILURE);
}
