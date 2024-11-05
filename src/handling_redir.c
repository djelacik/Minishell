#include "../includes/minishell.h"

int	handle_redir_input(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("error");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("error");
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

int	handle_redir_output(const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		perror("error");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("error");
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

int	handle_redir_append(const char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		perror("error");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("error");
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}


/*int	handle_redir_here_doc(const char *delimiter)
{

}*/

char	*redir_symb(char *input, int *index, t_tokens *tokens)
{
	char	*symbol;

	symbol = NULL;
	if (input[*index] == '<')
	{
		if (input[*index + 1] == '<')
		{
			tokens->token_type = REDIR_HERE_DOC;
			symbol = ft_strndup("<<", 2);
			(*index) += 2;
		}
		else
		{
			tokens->token_type = REDIR_INPUT;
			symbol = ft_strndup("<", 1);
			(*index)++;
		}
	}
	else if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
		{
			tokens->token_type = REDIR_APPEND;
			symbol = ft_strndup(">>", 2);
			(*index) += 2;
		}
		else
		{
			tokens->token_type = REDIR_OUTPUT;
			symbol = ft_strndup(">", 1);
			(*index)++;
		}
	}
	return (symbol);
}
