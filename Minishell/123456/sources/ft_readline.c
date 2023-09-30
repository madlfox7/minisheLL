
#include "lib_for_minishell.h"

char *ft_readline(void)
{
    char *whitespaces;
    char *str;
    int i;

    whitespaces = " \t\r\n\v";
    str = readline("minishell>");
    i = 0;
    while(str[i] != '\0')
    {
        if(ft_strchr(whitespaces, str[i]))
            i++;
        else
            break;
    }
    if (str[i] != '\0')
        add_history(str);
    return (str);
}
