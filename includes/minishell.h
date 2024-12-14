#ifndef MINISHELL_H
# define MINISHELL_H

// valgrind -v --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell


//# define DEBUG_MIRE
#ifdef DEBUG_MIRE
# define mprint(...) printf( __VA_ARGS__)
#else
# define mprint(...) ((void)0)
#endif

# include "execution.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include <termios.h>

# define MALLOC_ERR "malloc error"
# define PIPE_ERR "pipe error"
# define DUP2_ERR "dup2 error"
# define EXEC_ERR "execution error"
# define EXECVE_ERR "execve error"
# define FORK_ERR "fork error"
# define OPEN_ERR "open error"
# define STRDUP_ERR "strdup error"

# define EMPTY 0
# define COMMAND 1
# define ARGUMENT 2
# define REDIR_INPUT 3
# define REDIR_OUTPUT 4
# define REDIR_APPEND 5
# define REDIR_HERE_DOC 6
# define PIPE 7
# define SPECIAL_SYMB 8

# define CONTINUE_PRO 2

extern int	g_exit_status;

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
	t_builtin	builtin_type;
}	t_tokens;

typedef struct s_id
{
	t_tokens	*tokens;
	int			*i;
	int			*j;
}	t_id;

typedef struct s_redirect
{
	char			*file;
	int				type;
}	t_redirect;

typedef struct s_data
{
	t_tokens		*args;
	int				token_count;
	int				cmnd_count;
	t_redirect		*redirs;
	int				redir_count;
	int				is_in_pipe;
}	t_data;

typedef struct s_cmnds
{
	t_data		*data;
	int			command_count;
	int			**pipes;
	int			pipe_count;
	pid_t		*pids;
	char		**env_cpy;
	t_env		*env_list;
	int			exited;
}	t_cmnds;

/* count_tokens.c */
int			count_quoted_tokens(char *input, int *i, \
		char quote_type, t_env **env_list);
int			count_unquoted_tokens(char *input, int *i, \
		t_env **env_list);
int			count_tokens(char *input, t_env **env_list);

/* free_functions.c */
void		free_exist_tokens(t_tokens *tokens, int index);
void		free_empty(char *input, t_tokens *tokens, int *j);
void		free_id_and_tokens(t_id *id, t_tokens *tokens, int j);
void		free_id(t_id *id);
void		free_data_fail(t_data *data, int count);

/* signals.c */
void		handle_sigint(int sig);

/* handling_env_var.c */
char		*environment_variable(char *input, int *index, t_env **env_list);
void		append_env(char *quoted_input, int *i, char *env_var);

/* handling_quotes.c */
int			calculate_single_len(char *input, int start_index, char quote_type);
char		*single_quotes(char *input, int *index);
int			calculate_double_len(char *input, int start_index, \
		char quote_type, t_env **env_list);
char		*double_quotes(char *input, int *index, t_env **env_list);
int			calculate_quotes_double(char *input);
int			calculate_quotes_single(char *input);

/* handling_pipes.c */
char		*handle_pipes(char *input, int *index, t_tokens *tokens);

/* handling_redir.c */
char		*redir_symb(char *input, int *index, t_tokens *tokens);
int			handle_redir_input(const char *file);
int			handle_redir_output(const char *file);
int			handle_redir_append(const char *file);
int			handle_redir_here_doc(const char *delimiter);

/* init_data.c */
t_data		*init_data(t_tokens *tokens);

/* init_data_utils.c */
int			count_commands(t_tokens *tokens);
int			count_args(t_tokens *tokens, int *index);
int			count_redirs(t_tokens *tokens, int *index);
t_data		*allocate_data(int command_count);
int			allocate_mem(t_data *data, int j, int arg_count, int redir_count);

/* main.c */
//int	main(int argc, char **argv, char **envp);

/* parsing.c */
t_tokens	*tokenize_input(char *input, t_env **env_list);

/* parse_init.c */
void		init_tokens(t_tokens *tokens, int count);
int			init_id_and_tokens(t_id *id, t_tokens **tokens, \
		char *input, t_env **env_list);

/* parse_utils.c */
t_builtin	builtin_type(char *command);
char		*ft_strndup(const char *src, size_t n);

/* parse_pro.c */
int			process_start(char *input, t_id *id);
int			process_redirs(char *input, t_id *id);
int			process_pipe(char *input, t_id *id);
int			process_dollar(char *input, t_id *id, t_env **env_list);

/* parse_pro2.c */
char		*singleq(char *input, int *i);
char		*doubleq(char *input, int *i, t_env **env_list);
int			process_quotes(char *input, t_id *id, t_env **env_list);

/* parse_pro3.c */
int			process_redir_arg(char *input, t_id *id, int start);
int			process_double_here_doc(char *input, t_id *id);
int			process_double_append(char *input, t_id *id);
int			process_output(t_id *id);
int			process_input(t_id *id);

/* parse_pro4.c */
int			process_rest_redir(char *input, t_id *id, int start);
int			process_rest_pipe(char *input, t_id *id, int start);
int			process_rest_args(char *input, t_id *id, int start);
int			process_rest(char *input, t_id *id, t_env **env_list);
int			process_rest_dollar(char *input, t_id *id, \
		int start, t_env **env_list);

/* signals.c */
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		here_doc_sig(int sig);

/* debug.c */
void		print_tokens(t_tokens *tokens, int token_count);
void		print_redirects(t_redirect *redirs, int redir_count);
void		print_data(t_data *data, int data_count);
void		print_cmnds(t_cmnds *cmnds);

void	free_struct_loop(t_cmnds *cmnds);

#endif
