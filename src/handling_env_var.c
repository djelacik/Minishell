#include "../includes/minishell.h"

char	*environment_variable(char *input, int *index, t_env **env_list)
{
	char	*var_name;
	char	*env_var;
	int		var_len;
	int		i;

	if (*env_list == NULL)
	{
			printf("error: env_list is NULL\n");
			return (ft_strdup(""));
	}
	var_len = 0;
	(*index)++;
	while (input[*index + var_len] && (ft_isalnum(input[*index + var_len]) || input[*index + var_len] == '_'))
		var_len++;
	var_name = malloc((var_len + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < var_len)
	{
		var_name[i] = input[*index + i];
		i++;
	}
	var_name[i] = '\0';
	(*index) += var_len;
	env_var = ft_getenv(var_name, *env_list);
	free(var_name);
	if (!env_var)
		return (ft_strdup(""));
	return (ft_strdup(env_var));
}
