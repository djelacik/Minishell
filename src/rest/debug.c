#include "../../includes/minishell.h"

void print_tokens(t_tokens *tokens, int token_count)
{
    int i = 0;

    while (tokens[i].token_string && i < token_count)
    {
        dbg_print("  Token[%d]:\n", i);
        dbg_print("    Token String: %s\n", tokens[i].token_string);
        dbg_print("    Token Type: %d\n", tokens[i].token_type);
        dbg_print("    Builtin Type: %d\n", tokens[i].builtin_type);
        i++;
    }
}

void print_redirects(t_redirect *redirs, int redir_count)
{
    int i = 0;
    (void)redirs;

    while (i < redir_count)
    {
        dbg_print("  Redirect[%d]:\n", i);
        dbg_print("    File: %s\n", redirs[i].file);
        dbg_print("    Type: %d\n", redirs[i].type);
        i++;
    }
}

void print_data(t_data *data, int data_count)
{
    int i = 0;

    while (i < data_count)
    {
        dbg_print("Command[%d]:\n", i);
        dbg_print("  Token Count: %d\n", data[i].token_count);
        dbg_print("  Redirect Count: %d\n", data[i].redir_count);
        if (data[i].args)
        {
            dbg_print("  Tokens:\n");
            print_tokens(data[i].args, data[i].token_count);
        }
        if (data[i].redirs)
        {
            dbg_print("  Redirects:\n");
            print_redirects(data[i].redirs, data[i].redir_count);
        }
        i++;
    }
}

void print_cmnds(t_cmnds *cmnds)
{
    //int i = 0;

    dbg_print("Command Count: %d\n", cmnds->data->cmnd_count);
    dbg_print("Pipe Count: %d\n", cmnds->pipe_count);

    dbg_print("Commands:\n");
    print_data(cmnds->data, cmnds->data->cmnd_count);
}
