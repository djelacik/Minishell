/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaakkol <mjaakkol@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:37:03 by mjaakkol          #+#    #+#             */
/*   Updated: 2024/12/20 10:37:22 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_global(t_cmnds *cmnds)
{
	if (!cmnds)
		return ;
	free_env_list(&cmnds->env_list);
	free_array(cmnds->env_cpy);
}

int	error_exit(t_cmnds *cmnds, char *error_msg, int error_code)
{
	free_structs(cmnds);
	if (error_msg)
		printf("%s\n", error_msg);
	exit(error_code);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
