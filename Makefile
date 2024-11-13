NAME = minishell

SOURCES = \
		src/handling_env_var.c \
		src/handling_quotes.c \
		src/handling_redir.c \
		src/parsing.c \
		src/builtins/exec_builtin.c \
		src/builtins/enviroment.c \
		src/builtins/env_utils.c \
		src/execution/test_main.c 
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
