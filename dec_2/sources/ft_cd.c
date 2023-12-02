#include "lib_for_minishell.h"

// t_environment_list *change_node_by_name(t_environment_list **envp,  char *name, char *value) ;


  t_environment_list *find_node_by_name(t_environment_list *envp,  char *name) ;

//cd petqa stexci OLDPWD dasht u edtex dni getcwd-n minchev chdir anely


t_environment_list *change_node_by_name(t_environment_list **envp,  char *name, char *value) //funckia node val poxelu hamar, petqa poxi realy voch te kopian, bayc der chi anum
{
    while (*envp != NULL)
     {
        if ((*envp)->name_and_value != NULL && (*envp)->name_and_value[0] != NULL &&
            streq((*envp)->name_and_value[0], name))
            {
                (*envp)->name_and_value[1] = ft_strdup(value);
                return *envp;
            }
        *envp = (*envp)->next;
    }
    return NULL;
}

void ft_cd(char **str, t_environment_list **envp, int exit_num) 
{
    printf("Hi cd\n");

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
    char *old_pwd = NULL;
    old_pwd = ft_strdup(getcwd(NULL, 0)); //vercnuma current working dir path
    
    if (chdir(path) != 0) //changes dir
     {
        perror("chdir");
        free(path);
     if (exit_num == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
    exit_status_msh = EXIT_FAILURE; //or error code of chdir?
     return;
    }
       if (old_pwd != 0) //ete stacvela
         {
             t_environment_list *old_pwd_node = find_node_by_name(*envp, "OLDPWD"); //gtnuma OLDPWD ete ka
          if (old_pwd_node == NULL || old_pwd_node->name_and_value[1] == NULL || !(*old_pwd_node->name_and_value[1])) //ete chka stexcuma oldpwd  kam unset araca
               {
                     t_environment_list *newNode;
        
                 newNode = ft_list_new_for_export("OLDPWD", old_pwd);  //nor listi ptr (CREATING NEW LIST
               //  t_environment_list *current = *envp;  
                     ft_list_add_back_for_environment(envp, newNode);
                    printf("stexcel node add backov u add old_pwd\n"); 
               }
        else
              {
                  change_node_by_name(envp,  "OLDPWD", old_pwd);
                  set_last_node(envp, 1);
                 printf("update OLDPWD value by old_pwd\n");
              }
         }
    free(path);
    free(old_pwd);
    
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



