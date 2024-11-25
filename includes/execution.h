
#ifndef EXECUTION_H
# define EXECUTION_H

//# define DEBUG
#ifdef DEBUG 
# define dbg_print(...) fprintf(stderr, __VA_ARGS__)
#else
# define dbg_print(...) ((void)0)
#endif

struct s_command;
typedef struct s_command t_command;

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

int			exec_echo(t_command *command);
int			exec_pwd(void);
void		update_pwd(t_env **head);
void		ft_cd(t_command *command);
void		ft_exit(t_command *command);

//env func prototypes
void		init_list(t_env **head, char **envp);
void		add_node(t_env **head, const char *key, const char *value);
void		lst_add_back(t_env **head, t_env *new_node);
char		*save_pairs(char *token_string, char **value_p);

void		ft_env(t_env *head);
void		export_add(t_env **head, t_command *command);
void		export_print(t_env *head);
void		single_unset(t_env **head, const char *key);
void		ft_unset(t_env **head, t_command *command);
void		free_env_list(t_env **head);
char		*ft_getenv(char *key, t_env *head);
void		ft_setenv(char *key, char *value, t_env **head);

//pipe func prototypes
void		setup_pipes(int i, int command_count, int pipefd[2]);
void		setup_pids(t_cmnds *cmnds);
void		close_unused_pipes(int current, t_cmnds *cmnds);

//process func prototypes
int			fork_process(int i, int fd_in, int pipefd[2], t_cmnds *cmnds);
void		child_process(int i, int fd_in, int pipe_fd[2], t_cmnds *cmnds);
void		execute_command(t_data *data, t_cmnds *cmnds);
void		wait_for_children(t_cmnds *cmnds);
void		handle_heredoc(char *delimiter);

//execution func protoypes
void		*find_path(char *command, t_cmnds *cmnds);
void		free_array(char **array);

#endif
