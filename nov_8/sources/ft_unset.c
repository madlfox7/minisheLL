
// #include "lib_for_minishell.h"



// void unset(t_environment_list **head, const char *name)
// {
//     if (*head == NULL) 
//         return;

//     if (ft_strncmp((*head)->name_and_value[0], name, ft_strlen((*head)->name_and_value[0])) == 0)
//     {
//         t_environment_list *temp = *head;
//         *head = (*head)->next;
//         free(temp->name_and_value[0]);
//         free(temp->name_and_value[1]);
//         free(temp->name_and_value);
//         free(temp);
//         return;
//     }
    
  
//     t_environment_list *current = *head;
//     t_environment_list *prev = NULL;
//     while (current != NULL) {
//         if (ft_strncmp(current->name_and_value[0], name, ft_strlen((*head)->name_and_value[0])) == 0) {
//             prev->next = current->next;
//             free(current->name_and_value[0]);
//             free(current->name_and_value[1]);
//             free(current->name_and_value);
//             free(current);
//             return;
//         }
//         prev = current;
//         current = current->next;
//     }
// }




// void ft_unset(char **str, t_environment_list **envp)
// {
  
//    int i = 0;

//     if (!str || !(*str) || !streq(str[i], "unset"))  //ete datarka kam unset chi ( DO NOTHING)
//         return;

//     while (str[i])     
//     {

//         if (i == 0 && streq(str[i], "unset")) //skip unset(first)
//             i++;
//         if (!str[i])            //unset without arguments
//             break;
//         char *name = ft_strdup(str[i]);
    
//             t_environment_list *newNode = ft_list_new_for_export(str[i]);  //nor listi ptr (CREATING NEW LIST) 

//             unset(envp, name);
//         i++;
//      }
//      ft_env(*newNode);
// }




