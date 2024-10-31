/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:44:43 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/30 16:06:11 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc
# include <readline/readline.h> //readline
# include <readline/history.h> //readline, add_history

# define EMPTY 0
# define COMMAND 1
# define ARGUMENT 2

typedef struct s_tokens
{
	char	*token_string;
	int		token_type;
}	t_tokens;

/* main.c */
int	main(int argc, char **argv);

/* parsing.c */
t_tokens	*tokenize_input(char *input);

#endif
