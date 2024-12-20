#include "../../includes/minishell.h"

void	append_env(char *quoted_input, int *i, char *env_var)
{
	int	j;

	j = 0;
	while (env_var[j])
		quoted_input[(*i)++] = env_var[j++];
}

static char	*increment_here(char *input, int *index, int *var_len)
{
	(void)input;
	(*index)++;
	(*var_len)++;
	return (ft_strdup("$"));
}

static char	*increment_here_d(char *input, int *index, int *var_len)
{
	(void)input;
	(*index) += 2;
	(*var_len) += 2;
	return (ft_strdup("?"));
}

static char	*extract_env_var(char *input, int *index, int *var_len)
{
	char	*var_name;
	int		i;

	*var_len = 0;
	if (input[*index] == '$' && input[*index + 1] == '?')
		return (increment_here_d(input, index, var_len));
	if (input[*index] == '$' && (input[*index + 1] == '\0' || \
				(ft_isalnum(input[*index + 1]) != 1 && \
				input[*index + 1] != '_')))
		return (increment_here(input, index, var_len));
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

	var_name = extract_env_var(input, index, &var_len);
	if (!var_len)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
	{
		free(var_name);
		return (ft_itoa(g_exit_status));
	}
	if (ft_strcmp(var_name, "$") == 0)
	{
		free(var_name);
		return (ft_strdup("$"));
	}
	else
		env_var = ft_getenv(var_name, *env_list);
	free(var_name);
	if (!env_var)
		return (ft_strdup(""));
	return (ft_strdup(env_var));
}
