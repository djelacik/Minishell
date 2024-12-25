
#ifndef EXECUTION_H
# define EXECUTION_H

//# define DEBUG
#ifdef DEBUG 
# define dbg_print(...) fprintf(stderr, __VA_ARGS__)
#else
# define dbg_print(...) ((void)0)
#endif

struct s_tokens;
typedef struct s_tokens t_tokens;

struct s_data;
typedef struct s_data t_data;

struct s_cmnds;
typedef struct s_cmnds t_cmnds;

typedef enum e_redir_type
{
	REDIRECT_INPUT,		// <
	REDIRECT_OUTPUT,	// >
	REDIRECT_APPEND,	// >>
	REDIRECT_HEREDOC	// <<
}	t_redir_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int			exec_echo(t_data *data);
int			exec_pwd(void);
void		update_pwd(t_env **head);
void		ft_cd(t_data *data, t_env **head);
void		ft_exit(t_data *data, t_cmnds *cmnds);
int			is_builtin(char *command);
void		execute_builtin(t_data *data, t_cmnds *cmnds);

//env func prototypes
void		init_list(t_env **head, char **envp);
void		add_node(t_env **head, const char *key, const char *value);
void		lst_add_back(t_env **head, t_env *new_node);
char		*save_pairs(char *token_string, char **value_p);

void		ft_env(t_env *head);
void		export_add(t_env **head, t_data *data);
void		export_print(t_env *head);
void		single_unset(t_env **head, char *key);
void		ft_unset(t_env **head, t_data *data);
void		free_env_list(t_env **head);
int			get_lst_size(t_env *lst);
char		*ft_getenv(char *key, t_env *head);
void		ft_setenv(char *key, char *value, t_env **head);
void		update_env_cpy(t_cmnds *cmnds);

//pipe func prototypes
void		setup_pipes(int i, int command_count, int pipefd[2]);
void		close_unused_pipes(int current, t_cmnds *cmnds);

//process func prototypes
void		start_process(t_cmnds *cmnds);
void		child_process(int i, int fd_in, int pipe_fd[2], t_cmnds *cmnds);
void		execute_external(t_data *data, t_cmnds *cmnds);
void		handle_redirections(t_data *cmnd_data, t_cmnds *cmnds);
void		handle_redirections_parent(t_data *cmnd_data);
void		handle_heredoc(t_cmnds *cmnds, char *delimiter);
void		handle_heredoc_parent(char *delimiter);

//execution func protoypes

void		*find_path(char *command, t_cmnds *cmnds);
void		lst_to_arr(t_cmnds *cmnds);
void		free_array(char **array);
int			error_exit(t_cmnds *cmnds, char *error_msg, int error_code);

void		handle_redirection(t_data *cmnd_data);
void		setup_pids(t_cmnds *cmnds);
int			fork_process(int i, int fd_in, int pipefd[2], t_cmnds *cmnds);


#endif
