#include "../../includes/minishell.h"

void print_tokens(t_tokens *tokens, int token_count)
{
    int i = 0;

    while (tokens[i].token_string && i < token_count)
    {
        mprint("  Token[%d]:\n", i);
        mprint("    Token String: %s\n", tokens[i].token_string);
        mprint("    Token Type: %d\n", tokens[i].token_type);
        mprint("    Builtin Type: %d\n", tokens[i].builtin_type);
        i++;
    }
}

void print_redirects(t_redirect *redirs, int redir_count)
{
    int i = 0;
    (void)redirs;

    while (i < redir_count)
    {
        mprint("  Redirect[%d]:\n", i);
        mprint("    File: %s\n", redirs[i].file);
        mprint("    Type: %d\n", redirs[i].type);
        i++;
    }
}

void print_data(t_data *data, int data_count)
{
    int i = 0;

    while (i < data_count)
    {
        mprint("Command[%d]:\n", i);
        mprint("  Token Count: %d\n", data[i].token_count);
        mprint("  Redirect Count: %d\n", data[i].redir_count);
        if (data[i].args)
        {
            mprint("  Tokens:\n");
            print_tokens(data[i].args, data[i].token_count);
        }
        if (data[i].redirs)
        {
            mprint("  Redirects:\n");
            print_redirects(data[i].redirs, data[i].redir_count);
        }
        i++;
    }
}

void print_cmnds(t_cmnds *cmnds)
{
    //int i = 0;

    mprint("Command Count: %d\n", cmnds->data->cmnd_count);
    mprint("Pipe Count: %d\n", cmnds->pipe_count);

    mprint("Commands:\n");
    print_data(cmnds->data, cmnds->data->cmnd_count);
}

/*static void	print_cmnd_args(t_data *data, int index)
{
	int	i;

	i = 0;
	while (data[index].args[i].token_string)
	{
		printf("args[%d]: %s type: %d builtin: %d\n", i, data[index].args[i].token_string, data[index].args[i].token_type, data[index].args[i].builtin_type);
		i++;
	}
}*/

/*static void	print_tokens(t_tokens *tokens)
{
	int i;

	i = 0;
	while (tokens[i].token_string)
	{
		printf("%s ", tokens[i].token_string);
		if (tokens[i].token_type == COMMAND)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == ARGUMENT)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_INPUT)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_OUTPUT)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_APPEND)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == REDIR_HERE_DOC)
			printf("token type: %d, builtin type: %d\n", tokens[i].token_type, tokens[i].builtin_type);
		else if (tokens[i].token_type == PIPE)
			printf("token type: %d, builtin type %d\n", tokens[i].token_type, tokens[i].builtin_type);
		i++;
	}
}

static void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("redir count: %d\n", data->redir_count);
	printf("command count: %d\n", data->cmnd_count);
	printf("token count : %d\n", data->token_count);
	while (i < data->cmnd_count)
	{
		print_cmnd_args(data, i);
		i++;
	}

}*/
