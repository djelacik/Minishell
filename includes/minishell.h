/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:44:43 by djelacik          #+#    #+#             */
/*   Updated: 2024/11/02 19:36:25 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "execution.h"
# include "../libft/libft.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc
# include <readline/readline.h> //readline
# include <readline/history.h> //readline, add_history

# define EMPTY 0
# define COMMAND 1
# define ARGUMENT 2

typedef enum e_builtin
{
	BUILTIN_NONE,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin;

typedef struct s_tokens
{
	char		*token_string;
	int			token_type;
	t_builtin	builtin_type; // builtin commands are executed differently, so we use a enum for type.
}	t_tokens;

typedef struct s_tarray // test struct
{
	t_tokens	**token_array;
	int			token_count;
}	t_tarray;

/* handling_env_var.c */
char *environment_variable(char *input, int *index);

/* handling_quotes.c */
int	calculate_single_len(char *input, int start_index, char quote_type);
char *single_quotes(char *input, int *index);
int	calculate_double_len(char *input, int start_index, char quote_type);
char *double_quotes(char *input, int *index);
char *handling_quotes(char *input, int *index);

/* main.c */
int	main(int argc, char **argv);

/* parsing.c */
t_tokens	*tokenize_input(char *input);

#endif

