
#include "lib_for_minishell.h"

int    get_env(t_environment_list *envp);



void    ft_pwd(char **str, t_environment_list **envp, int exit_num)
{
    printf("Hi PWD\n");
    char    *path_name;
    (void)str;
    // if (!str || !(*str))
    //     return ;
    // if (!(streq(*(str), "pwd")) )
    //     return ;

    path_name = getcwd(NULL, 0); //current working directory path
    if (!path_name) //ete chka
    {
        if (get_env(*envp) == 0) //error code 127? //cannot get env  u env path chka
        {
            perror("pwd"); //pwd error berum

            if (exit_num == BUILTIN_EXIT)
                exit(EXIT_FAILURE);
           // exit_status_msh =
            return ;
        }

        return ;
    }
    else
    {
        printf("%s\n",  path_name); //tpuma path_name
        free(path_name); //free anum
         exit_status_msh = 0;
         printf("Bye Pwd\n");
         if (exit_num == BUILTIN_EXIT)
                exit(EXIT_SUCCESS);
   
        //return ;
    }
   
       
}



int    get_env(t_environment_list *envp) //mer env listic vercnuma PWD value-n
{
    while (envp)
    {
        if (streq(envp->name_and_value[0], "PWD")) //pntruma PWD anunov, tpum da, veradarznum 1
        {
            printf("%s\n", envp->name_and_value[1]);
            return (1);
        }
        envp = envp->next;
    }
    return (0);
}