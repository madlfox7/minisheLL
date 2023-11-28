#include "lib_for_minishell.h"



  t_environment_list *find_node_by_name(t_environment_list *envp,  char *name) ;

void ft_cd(char **str, t_environment_list **envp, int exit_num) 
{
    printf("Hi cd\n");
    (void)*envp;
    if (!str || !(*str) || !streq(str[0], "cd")) 
        return;
    int i = 1;
    char *path = NULL;
    if (!str[i] || !(*str[i]) || streq(str[i], "~"))
    {
        path = "HOME";
        t_environment_list *home_node = find_node_by_name(*envp, path);
          if (home_node == NULL || home_node->name_and_value[1] == NULL || !(*home_node->name_and_value[1]))
                path = ft_strdup(getenv("HOME"));  //getting path from original env, if home usnet or HOME value is set to null
        else
                path = ft_strdup(home_node->name_and_value[1]);  //if HOME i 
    }
    else
        path=ft_strdup(str[i]);
    if (path == NULL)  
     {
        printf("Invalid path for cd\n");
        if (exit_num == BUILTIN_EXIT)
            exit(EXIT_FAILURE); //or error code of chdir?
    exit_status_msh = EXIT_FAILURE;
        //return;
    }
    if (chdir(path) != 0) //changes dir
     {
        perror("chdir");
        free(path);
     if (exit_num == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
    exit_status_msh = EXIT_FAILURE; //or error code of chdir?
        //return;
    }
    free(path);


    char cwd[1024];


    if (getcwd(cwd, sizeof(cwd)) != NULL) //gets current working directory //jnjel 
        printf("Current directory: %s\n", cwd);
    else
        perror("getcwd"); 
    if (exit_num == BUILTIN_EXIT)
        exit(EXIT_SUCCESS);
    exit_status_msh = 0;
}


t_environment_list *find_node_by_name(t_environment_list *envp,  char *name) 
{
    while (envp != NULL)
     {
        if (envp->name_and_value != NULL && envp->name_and_value[0] != NULL &&
            streq(envp->name_and_value[0], name))
            return envp;
        envp = envp->next;
    }
    return NULL;
}

