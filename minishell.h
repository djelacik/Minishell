#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h> //printf
# include <stdlib.h> // malloc

typedef	struct	s_tokens
{
	char	*token_string;
	int		token_type;
} t_tokens;

/* main.c */
int	main(int argc, char **argv);

#endif
