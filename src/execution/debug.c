#include "../../includes/minishell.h"

void print_tokens(t_tokens *tokens, int token_count)
{
    int i = 0;

    while (i < token_count)
    {
        dbg_printf("  Token[%d]:\n", i);
        dbg_printf("    Token String: %s\n", tokens[i].token_string);
        dbg_printf("    Token Type: %d\n", tokens[i].token_type);
        dbg_printf("    Builtin Type: %d\n", tokens[i].builtin_type);
        i++;
    }
}

void print_redirects(t_redirect *redirs, int redir_count)
{
    int i = 0;

    while (i < redir_count)
    {
        dbg_printf("  Redirect[%d]:\n", i);
        dbg_printf("    File: %s\n", redirs[i].file);
        dbg_printf("    Type: %d\n", redirs[i].type);
        i++;
    }
}

void print_data(t_data *data, int data_count)
{
    int i = 0;

    while (i < data_count)
    {
        dbg_printf("Command[%d]:\n", i);
        dbg_printf("  Token Count: %d\n", data[i].token_count);
        dbg_printf("  Redirect Count: %d\n", data[i].redir_count);
        if (data[i].args)
        {
            dbg_printf("  Tokens:\n");
            print_tokens(data[i].args, data[i].token_count);
        }
        if (data[i].redirs)
        {
            dbg_printf("  Redirects:\n");
            print_redirects(data[i].redirs, data[i].redir_count);
        }
        i++;
    }
}

void print_cmnds(t_cmnds *cmnds)
{
    int i = 0;

    dbg_printf("Command Count: %d\n", cmnds->command_count);
    dbg_printf("Pipe Count: %d\n", cmnds->pipe_count);

    if (cmnds->data)
    {
        dbg_printf("Commands:\n");
        print_data(cmnds->data, cmnds->command_count);
    }
}
