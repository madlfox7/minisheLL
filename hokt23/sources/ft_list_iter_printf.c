
#include "lib_for_minishell.h"


void env(t_environment_list *env_list)
{
	   t_environment_list *current = env_list;
	        while (current != NULL)
     {
        printf("%s=%s\n", current->name_and_value[0], current->name_and_value[1]);
         current = current->next;
     }
} 


void unset(t_environment_list **head, const char *name) {
  
    if (*head == NULL) {
        return;
    }

    if (strcmp((*head)->name_and_value[0], name) == 0) {
        t_environment_list *temp = *head;
        *head = (*head)->next;
        free(temp->name_and_value[0]);
        free(temp->name_and_value[1]);
        free(temp->name_and_value);
        free(temp);
        return;
    }
    t_environment_list *current = *head;
    t_environment_list *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name_and_value[0], name) == 0) {
            prev->next = current->next;
            free(current->name_and_value[0]);
            free(current->name_and_value[1]);
            free(current->name_and_value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}


void export(t_environment_list **head, const char *name, const char *value) {
    if (*head == NULL) {

        t_environment_list *new_node = (t_environment_list *)malloc(sizeof(t_environment_list));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        new_node->name_and_value = (char **)malloc(2 * sizeof(char *));
        if (new_node->name_and_value == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }  
        new_node->name_and_value[0] = strdup(name);
        new_node->name_and_value[1] = strdup(value);
        
     
        new_node->next = NULL;
        
       
        *head = new_node;
    } else {
    
        t_environment_list *current = *head;
        while (current != NULL) {
            if (strcmp(current->name_and_value[0], name) == 0) {
              
                free(current->name_and_value[1]);
                current->name_and_value[1] = strdup(value);
                return;
            }
            current = current->next;
        }
        
       
        t_environment_list *new_node = (t_environment_list *)malloc(sizeof(t_environment_list));
        if (new_node == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        
        new_node->name_and_value = (char **)malloc(2 * sizeof(char *));
        if (new_node->name_and_value == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
        
        new_node->name_and_value[0] = strdup(name);
        new_node->name_and_value[1] = strdup(value);
        new_node->next = NULL;
        
     
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        

        current->next = new_node;
    }
}


// void env_builtins(void)
// {
//     t_environment_list *env_list = NULL;

//     export(&env_list, "PATH", "/usr/bin");
//     export(&env_list, "HOME", "/home/user");
//     export(&env_list, "USER", "user");


//     printf("Environment variables:\n");
//     t_environment_list *current = env_list;
//     while (current != NULL)
//     {
//         printf("%s=%s\n", current->name_and_value[0], current->name_and_value[1]);
//         current = current->next;
//     }

   //   unset(&env_list, "HOME");

//    printf("Environment variables:\n");
//     current = env_list;
//     while (current != NULL)
//     {
//         printf("%s=%s\n", current->name_and_value[0], current->name_and_value[1]);
//         current = current->next;
//     }

//     current = env_list;
//     while (current != NULL) {
//         free(current->name_and_value[0]);
//         free(current->name_and_value[1]);
//         t_environment_list *temp = current;
//         current = current->next;
//         free(temp->name_and_value);
//         free(temp);
//     }

//     return 0;
//}




int	ft_strncmp_k(const char *s1, const char *s2, size_t	n)
{
	size_t	i;

	i = 0;
    if (!s1 || !s2)
        return 1;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	ft_list_iter_printf_for_token(t_token_list	*list,	int (f)(const char *, ...))
{
	t_token_list	*tmp;
	int i;

	if (!list || !f)
		return ;
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		f("TOKEN_INDEX[%d]\n", i);
		f("TOKEN_TYPE:::%d\n", tmp->type);
		f("TOKEN_VALUE:::%s\n", tmp->value);
		f("TOKEN_NEXT:::%d\n", tmp->next > 0);
		tmp = tmp->next;
		i++;
	}
	return ;
}
int  not_only_env(t_token_list *list, t_environment_list *env_list)
{
	//int i = 0;
	int flag = 0;
	int other_syms = 0;

	if (!list)
		return 0;
	int count = 0;

	t_token_list *tmp = list;
	while (tmp != NULL)
	{
		if (ft_strncmp_k(tmp->value, "env", 3) == 0 && ft_strlen(tmp->value) - 3 == 0)
			count++;
		else if (tmp->type != SEP && tmp->value != NULL)
		{	
			other_syms = 1;
		}
		if (count > 1 || other_syms)
		{
			printf("more than one env || other symbs found\n");
			return 1;
		}
		tmp = tmp->next;
	}
	printf("---------------------------------------ONLY ENV\n");
	env(env_list);
	return flag;
}

void iteri(t_token_list	*list, t_environment_list *envp)
{
	t_token_list	*tmp;
	int i;
   
	if (!list)
		return ;
	tmp = list;
	i = 0;
	printf(" %d\n", not_only_env(list, envp));

	while (tmp != NULL)
	 {
		 if (tmp->type == WORD &&  ft_strlen(tmp->value) - 6 == 0 && ft_strncmp(tmp->value, "export", 6) == 0) //if first word is env, and no other simbs : envp penv and no arg //lstsize no good
		// //if not only env use execve 
		{
			export(&)
		}
	// 	f("TOKEN_INDEX[%d]\n", i);
	// 	f("TOKEN_TYPE:::%d\n", tmp->type);
	// 	f("TOKEN_VALUE:::%s\n", tmp->value);
	// 	f("TOKEN_NEXT:::%d\n", tmp->next > 0);
		tmp = tmp->next;
		i++;
	}
	return ;
}


void	ft_list_iter_printf_for_environment(t_environment_list	*list, int (f)(const char *, ...))
{
	t_environment_list	*tmp;
	int i;

	if (!list || !f)
		return ;
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		f("ENVP_INDEX[%d]\n", i);
		f("ENVP_NAME_AND_VALUE[0]:::%s\n", tmp->name_and_value[0]);
		f("ENVP_NAME_AND_VALUE[1]:::%s\n", tmp->name_and_value[1]);
		tmp = tmp->next;
		i++;
	}
	return ;
}