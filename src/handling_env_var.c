#include "../includes/minishell.h"

void	append_env(char *quoted_input, int *i, char *env_var)
{
	int	j;

	j = 0;
	while (env_var[j])
		quoted_input[(*i)++] = env_var[j++];
}

static char	*extract_env_var(char *input, int *index, int *var_len)
{
	char	*var_name;
	int		i;

	*var_len = 0;
	(*index)++;
	while (input[*index + *var_len] && (ft_isalnum(input[*index + *var_len]) \
				|| input[*index + *var_len] == '_'))
		(*var_len)++;
	var_name = malloc((*var_len + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	i = -1;
	while (++i < *var_len)
		var_name[i] = input[*index + i];
	var_name[i] = '\0';
	*index += *var_len;
	return (var_name);
}

char	*environment_variable(char *input, int *index, t_env **env_list)
{
	char	*var_name;
	char	*env_var;
	int		var_len;

	if (*env_list == NULL)
	{
		printf("error: env_list is NULL\n");
		return (ft_strdup(""));
	}
	var_name = extract_env_var(input, index, &var_len);
	if (!var_len)
		return (NULL);
	env_var = ft_getenv(var_name, *env_list);
	free(var_name);
	if (!env_var)
		return (ft_strdup(""));
	return (ft_strdup(env_var));
}
