NAME = minishell

SOURCES = \
		src/parsing/handling_env_var.c \
		src/parsing/handling_double_q.c \
		src/parsing/handling_single_q.c \
		src/parsing/handling_pipes.c \
		src/parsing/handling_redir.c \
		src/parsing/count_tokens.c \
		src/parsing/free_functions.c \
		src/parsing/init_data.c \
		src/parsing/init_data_utils.c \
		src/parsing/parsing.c \
		src/parsing/parse_init.c \
		src/parsing/parse_utils.c \
		src/parsing/parse_pro.c \
		src/parsing/parse_pro2.c \
		src/parsing/parse_pro3.c \
		src/parsing/parse_pro4.c \
		src/parsing/parse_prod.c \
		src/parsing/parse_pro_extra.c \
		src/builtins/env_utils.c \
		src/builtins/env_utils2.c \
		src/builtins/enviroment.c \
		src/builtins/exec_builtin.c \
		src/builtins/export.c \
		src/execution/exec_utils.c \
		src/execution/exec.c \
		src/execution/pipes.c \
		src/execution/setup_start.c \
		src/redirs/child_process.c \
		src/redirs/here_doc.c \
		src/redirs/redirs.c \
		src/rest/free.c \
		src/rest/free2.c \
		src/signals.c \
		src/main.c \
		src/rest/debug.c \
		#src/rest/test_main.c 
		#src/signals.c
		#src/main.c 

OBJECTS = $(SOURCES:.c=.o)

LIBFT = ./libft/libft.a

CC = cc

CFLAGS += -g -Wall -Wextra -Werror

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
