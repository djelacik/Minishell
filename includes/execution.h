
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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int			exec_echo(char **args);
int			exec_pwd(void);
void		update_pwd(void);
void		ft_cd(t_command *command);
void		ft_exit(t_command *command);

//env func prototypes
void		init_list(t_env **head, char **envp);
void		lst_add_back(t_env **head, const char *key, const char *value);
void		rotate_add(t_env **head, t_env *new_node);

void		ft_env(t_env *head);
//void		export_add(t_env **head, const char *line);
void		export_add(t_env **head, t_command *command);
void		ft_unset(t_env **head, const char *key);
void		free_env_list(t_env **head);

#endif
