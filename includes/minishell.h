
#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG_MIRE
#ifdef DEBUG_MIRE
# define m_printf(...) printf( __VA_ARGS__)
#else
# define m_printf(...) ((void)0)
#endif

# include "execution.h"
# include "../libft/libft.h"
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc
# include <readline/readline.h> //readline
# include <readline/history.h> //readline, add_history
# include <unistd.h> //dup2
# include <fcntl.h> //open
# include <signal.h> //signal
# include <sys/wait.h>
# include <limits.h>


#define MALLOC_ERR "malloc error\n"
#define PIPE_ERR "pipe error\n"
#define DUP2_ERR "dup2 error\n"
#define EXEC_ERR "execution error\n"
#define EXECVE_ERR "execve error\n"
#define FORK_ERR "fork error\n"
#define OPEN_ERR "open error\n"
#define	STRDUP_ERR "strdup error\n"

# define EMPTY 0
# define COMMAND 1
# define ARGUMENT 2
# define REDIR_INPUT 3
# define REDIR_OUTPUT 4
# define REDIR_APPEND 5
# define REDIR_HERE_DOC 6
# define PIPE 7
# define SPECIAL_SYMB 8

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

typedef struct s_redirect {
	char			*file;
	int				type;
	//t_redir_type	type;
}	t_redirect;
				
					//token[0]	token[1]  token[2]   token[3]
					//echo		hello 		<		outfile
					
					// LATER tokens[0] tokens[1] 	| tokens[0] tokens[1]
					
						//commands[0] | commands[1]
typedef struct s_data //echo hello | grep "h"
{
	t_tokens		*args;			// Taulukko tokeneita
	int				token_count;	// Tokenien määrä
	int				cmnd_count;
	t_redirect		*redirs;			// Taulukko uudelleenohjauksia
	int				redir_count;		// Uudelleenohjausten määrä
}	t_data;

typedef struct s_cmnds
{
	t_data		*data;			// Taulukko `t_command`-rakenteita
	int			command_count;		// Komentojen määrä
	int			**pipes;
	int			pipe_count;
	pid_t		*pids;
	char		**env_cpy;
	t_env		*env_list;
} t_cmnds;

/* signals.c */
void	handle_sigint(int sig);

/* handling_env_var.c */
char *environment_variable(char *input, int *index, t_env **env_list);

/* handling_quotes.c */
int	calculate_single_len(char *input, int start_index, char quote_type);
char *single_quotes(char *input, int *index);
int	calculate_double_len(char *input, int start_index, char quote_type, t_env **env_list);
char *double_quotes(char *input, int *index, t_env **env_list);
int	calculate_quotes_double(char *input);
int	calculate_quotes_single(char *input);

/* handling_pipes.c */
char	*handle_pipes(char *input, int *index, t_tokens *tokens);

/* handling_redir.c */
char *redir_symb(char *input, int *index, t_tokens *tokens);
int	handle_redir_input(const char *file);
int	handle_redir_output(const char *file);
int	handle_redir_append(const char *file);
int	handle_redir_here_doc(const char *delimiter);

/* init_data.c */
t_data	*init_data(t_tokens *tokens);

/* main.c */
//int	main(int argc, char **argv, char **envp);

/* parsing.c */
t_tokens	*tokenize_input(char *input, t_env **env_list);
char *ft_strndup(const char *src, size_t n);

/* signals.c */
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

/* debug.c */
//void	print_tokens(t_tokens *tokens, int token_count);
//void	print_redirects(t_redirect *redirs, int redir_count);
//void	print_data(t_data *data, int data_count);
//void	print_cmnds(t_cmnds *cmnds);

#endif

