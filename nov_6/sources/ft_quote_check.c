#include "lib_for_minishell.h"

int     unclosed_quotes(char *input)
{
        int             i;
        int             S_quote;
        int             D_quote;

        i = 0;
        S_quote = 0;
        D_quote = 0;
        while (input[i])
        {
                if (input[i] == '\'' && !D_quote)
                        S_quote = !S_quote;
                else if (input[i] == '\"' && !S_quote)
                        D_quote = !D_quote;
                i++;
        }
        if (S_quote || D_quote)
        {
            printf("Error: Unclosed quote\n");
                return 1;
        }
        return 0;
}

