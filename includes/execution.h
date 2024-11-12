
#ifndef EXECUTION_H
# define EXECUTION_H

# define DEBUG
#ifdef DEBUG 
# define dbg_print(...) fprintf(stderr, __VA_ARGS__)
#else
# define dbg_print(...) ((void)0)
#endif

struct s_command;
typedef struct s_command t_command;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env	*next;
}	t_env;

int			exec_echo(char **args);
int			exec_pwd(void);
void		update_pwd(void);
void		ft_cd(t_command *command);
void		ft_exit(t_command *command);

#endif
