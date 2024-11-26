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

	path_value = get_value("PATH", cmnds->env_list);
	if (!path_value)
		return (NULL);
	paths = ft_split((const char *)path_value, ":");
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
