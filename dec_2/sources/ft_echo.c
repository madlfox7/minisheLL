#include "lib_for_minishell.h"



int n_set(char *str, int *suppress_nl);


void ft_echo(char **str, int exit_num)
{
    int i;
    int suppress_nl = 0;
    int word = 0;
    int flag_set = 0;

    i = 0;

    while(str[i] != NULL)
    {
        if (i == 0 && streq(str[i], "echo")) //skip first echo
            i++;
        if (!str[i]) 
            break ;
        if (ft_strlen(str[i]) >= 2 && n_set(str[i], &suppress_nl) && !word) // flag set and not after_word
        {
            flag_set = suppress_nl;
            i++;
        }
        else
        {  
            if (!flag_set) //no flag is set and -n is just an arg
                suppress_nl = 0;
            word = 1;
            printf("%s", str[i]);
            if (str[i + 1])
                printf(" ");
            i++;
        }
    }
    if (!suppress_nl)
        printf("\n");
  if (exit_num == BUILTIN_EXIT) 
        exit(EXIT_SUCCESS);
    exit_status_msh = 0;
        return ;
}




int n_set(char *str, int *suppress_nl)
{
    int i = 0;
  
    if (!str || !*str)
        return 0;
    if (str[i] == '-')
    {
        i++;
        while (str[i] == 'n') 
            i++;
        if (str[i] == '\0')
        {
            *suppress_nl = 1;
            return 1; 
        }
        else 
            return 0;
    } 
    return 0;
}