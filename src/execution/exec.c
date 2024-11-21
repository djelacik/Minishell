#include "../../includes/minishell.h"

char	*find_path(char *command, t_pipex *pp)
{
	int		i;
	char	*single_path;
	char	*full_path;

	i = 0;
	while (pp->envp[i] != NULL && ft_strncmp(pp->envp[i], "PATH=", 5) != 0)
		i++;
	if (pp->envp[i] == NULL)
	{
	//	perror(ERR_PATH);
	//command not found
		exit(127);
	}
	pp->paths = ft_split(pp->envp[i] + 5, ':');
	i = 0;
	while (pp->paths[i])
	{
		single_path = ft_strjoin(pp->paths[i++], "/");
		full_path = ft_strjoin(single_path, command);
		free(single_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	ft_free_strarray(pp->paths);
	return (NULL);
}


