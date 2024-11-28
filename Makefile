NAME = minishell

SOURCES = \
		src/handling_env_var.c \
		src/handling_double_q.c \
		src/handling_single_q.c \
		src/handling_pipes.c \
		src/handling_redir.c \
		src/init_data.c \
		src/parsing.c \
		src/builtins/env_utils.c \
		src/builtins/env_utils2.c \
		src/builtins/enviroment.c \
		src/builtins/exec_builtin.c \
		src/execution/exec_utils.c \
		src/execution/exec.c \
		src/execution/pipes.c \
		src/execution/setup_start.c \
		src/redirs/child_process.c \
		src/redirs/here_doc.c \
		src/redirs/redirs.c \
		src/rest/debug.c \
		src/rest/free.c \
		src/main.c \
		#src/rest/test_main.c 
		#src/signals.c
		#src/main.c 

OBJECTS = $(SOURCES:.c=.o)

LIBFT = ./libft/libft.a

CC = cc

CFLAGS += -Wall -Wextra -Werror -g

RM = rm -f

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
