
#include "lib_for_minishell.h"



void print_env(t_environment_list *env);



// void export(t_environment_list **head, const char *name, const char *value)
// {
//     if (*head == NULL)
//     {
//         t_environment_list *new_node = (t_environment_list *)malloc(sizeof(t_environment_list));
//         if (new_node == NULL)
//         {
//             perror("Memory allocation failed");
//             exit(1);
//         }
//         new_node->name_and_value = (char **)malloc(2 * sizeof(char *));
//         if (new_node->name_and_value == NULL)
//         {
//             perror("Memory allocation failed");
//             exit(1);
//         } 
//         new_node->name_and_value[0] = ft_strdup(name);
//         new_node->name_and_value[1] = ft_strdup(value);
//         new_node->next = NULL;   
//         *head = new_node;
//     }
//      else
//     {
//         t_environment_list *current = *head;
//         while (current != NULL)
//         {
//             if (strcmp(current->name_and_value[0], name) == 0)
//             {   
//                 free(current->name_and_value[1]);
//                 current->name_and_value[1] = strdup(value);
//                 return;
//             }
//             current = current->next;
//         }
        
//         t_environment_list *new_node = (t_environment_list *)malloc(sizeof(t_environment_list));
//         if (new_node == NULL)
//         {
//             perror("Memory allocation failed");
//             exit(1);
//         }
//         new_node->name_and_value = (char **)malloc(2 * sizeof(char *));
//         if (new_node->name_and_value == NULL)
//         {
//             perror("Memory allocation failed");
//             exit(1);
//         }
//         new_node->name_and_value[0] = ft_strdup(name);
//         new_node->name_and_value[1] = ft_strdup(value);
//         new_node->next = NULL;
        
//         current = *head;
//         while (current->next != NULL) 
//             current = current->next;
//         current->next = new_node;
//     }
// }



void ft_env(char **str, t_environment_list *envp)
{
    int i = 0;
    int many_env_err = 0;

     if (!streq(str[i], "env") || !str || !(*str))
        return ;
    while (str[i])
    {
        if (!streq(str[i], "env"))
        {
            many_env_err = 1;
            break ;
        }
            i++;
    }
    if (!many_env_err) 
        print_env(envp);
}


void print_env(t_environment_list *env)
{
     t_environment_list *current = env;
    while (current != NULL)
    {
        printf("%s=%s\n", current->name_and_value[0], current->name_and_value[1]);
        current = current->next;
    }
}