#include "lib_for_minishell.h"



char	*ft_strncpy(char *dest, char *src, unsigned int n);
int	ft_isalpha(int ch);
void print_export(t_environment_list *envp, int assigned_val);
int	ft_isalnum(int c);
size_t get_index_of_char(const char *str, char c);
int findEqualChar(const char *text);
int check_order(char *str);
int wrong_name(char *str, char *name);
t_environment_list *set_last_node(t_environment_list **envp, int flag);  //setting flag
int hasPlusEqual(char *str);
t_environment_list *ft_list_new_for_export(char *string_from_envp);
char	*ft_strnstr(char *str, char *to_find, size_t len);

int extract_name_and_value(char *String, char **name, char **value);

////////////////////////////////////////////////////////////////////////////////////////////////////


// typedef struct s_environment_list
// {
//     int envp_flag;
//     char **name_and_value;
//     struct s_environment_list *next;
// } t_environment_list;

// int findEqualChar(const char *text);
int ft_export(char **str, t_environment_list **envp)
{
    //printf("Hi from export\n");
     static int assigned_val; //if assigned, and than set again with no arg, don't remove from env list visibility 
     char *name = NULL;
     char *value = NULL;
     int i = 1;
     assigned_val = 1;
        if (!str[i])            //ete export aranc argumentneri  //tpel export listy
        { 
            print_export(*envp, assigned_val);   //no arg only export (PRINTING EXPORT LIST)
            printf("HERE\n");
            return 0;
        }
    while (str[i])     
    {
           if (!extract_name_and_value(str[i], &name, &value)) //if name and value
                name = ft_strdup(str[i]);
            if (!wrong_name(str[i], name)) //ete normal anunova
            {       

                // printf("[%s] [%s]\n",)
                t_environment_list *tmp = *envp;

            
                while (tmp)
                {
                    if (ft_strncmp(name, tmp->name_and_value[0], ft_strlen(name) + 1) == 0) //name arden ka
                    {
                        free(tmp->name_and_value[1]);
                        if (value == NULL)
                        {
                            //tmp->envp_flag = 0;   
                            tmp->name_and_value[1] = NULL; //do nothing 
                        }
                       if (value)
                        {
                            printf("HI\n");
                            tmp->envp_flag = 1;
                            printf("Changing value\n");
                            tmp->name_and_value[1] = ft_strdup(value);
                        }
                        break ;
                    }
                    tmp= tmp->next;
                }
                char *joined_str = ft_strjoin(name, "=");
                joined_str = ft_strjoin(name, value); //stugel value NULL linely
                t_environment_list *t = ft_list_new_for_environment(joined_str); 
                ft_list_add_back_for_environment(envp, t); 
                // if (!ft_strchr(str[i], '='))
                //     tmp->envp_flag = 0 ;
            }
             i++;
    }
     return (0);
}




int check_order(char *str) //check if += comes first return 1, else return 0;
{
    int equal_pos = 0;
    int plus_pos = 0;

    if (!str || !ft_strchr(str, '+')) 
        return 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            equal_pos=i;
            break;
        }
        else if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
        {
            plus_pos=i;
            break ;
        }
        i++;
    }
    if (plus_pos > equal_pos)
        return 1;
    return 0;
}




int extract_name_and_value(char *String, char **name, char **value) 
{
    char *delimiter_pos;

    int val_len;
    int name_len;
    int size = 1;                                                   //default = case
    delimiter_pos = ft_strchr(String, '=');                         //= position
    if (check_order(String)) //if valid +=          
    {
        size = 2;                                   
        delimiter_pos = ft_strnstr(String, "+=", strlen(String));   //+ position
    }
    if (delimiter_pos != NULL)                                      // if found = kam +=
    {
        name_len = delimiter_pos - String;                           
        val_len = ft_strlen(String) - name_len - size;
        *name = (char *)malloc((name_len + 1) * sizeof(char));
        *value = (char *)malloc((val_len + 1) * sizeof(char));
        if (*name && *value)
         {
            ft_strncpy(*name, String, name_len);
            (*name)[name_len] = '\0';
            ft_strncpy(*value, delimiter_pos + size, val_len);
            (*value)[val_len] = '\0';
            return 1;   //successfully extracted name and value
        } 
    } 
    return 0;               //if cannot extract name and value
}



int wrong_name(char *str, char *name)  //CHECKING NAME, returrn 1 if error
{
 
    if (!(name[0] == '_' ||  ft_isalpha(name[0])) || !name || !(*name))
    {
       // printf("HERE\n");
             printf("minishell: export: `%s': not a valid identifier\n", str);
        return 1;
    }
    int len = ft_strlen(name);
    int i = 0;

    while (i < len)
    {
        if (!(ft_isalnum(name[i]) || name[i] == '_')) 
        {
            //printf("ERROR\n");
            printf("minishell: export: `%s': not a valid identifier\n", name);
            return 1;
        }
        i++;
    }

    return 0;
}




t_environment_list *set_last_node(t_environment_list **envp, int flag)  //setting flag
{
    if (*envp == NULL) 
        return NULL; 

    t_environment_list *current = *envp;

    while (current->next != NULL) 
        current = current->next;

    current->envp_flag = flag;
    return current;
}



//add_new_node at the_end of_list
// t_environment_list *ft_list_new_for_export(char *string_from_envp)
// {
//     t_environment_list *result = (t_environment_list *)malloc(sizeof(t_environment_list));

//     size_t index;

//     if (!result)
//         return NULL;
//     if (check_order(string_from_envp))
//          index = get_index_of_char(string_from_envp, '+');
//     else
//         index = get_index_of_char(string_from_envp, '=');
//     result->name_and_value = (char **)malloc(2 * sizeof(char *));
//     if (!result->name_and_value)
//     {
//         free(result);
//         return NULL;
//     }
//     result->name_and_value[0] = (char *)malloc((index + 1) * sizeof(char));
//     result->name_and_value[1] = ft_strdup(string_from_envp + index + 1);
//     if (!result->name_and_value[0] || !result->name_and_value[1])
//     {
//         free(result->name_and_value[0]);
//         free(result->name_and_value[1]);
//         free(result->name_and_value);
//         free(result);
//         return NULL;
//     }
//     ft_strncpy(result->name_and_value[0], string_from_envp, index);
//     result->name_and_value[0][index] = '\0';
//     result->next = NULL;
//     return result;
// }



char	*ft_strnstr(char *str, char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	to_find_len;

	i = 0;
	to_find_len = ft_strlen(to_find);
	if (!str && !len)
		return (NULL);
	if (to_find_len == 0)
		return (str);
	while (str[i] && (i + to_find_len) <= len)
	{
		j = 0;
		while (to_find[j] && str[i + j] == to_find[j])
			j++;
		if (j == to_find_len)
			return (str + i);
		i++;
	}
	return (NULL);
}





int plus_before_eq(char* str) 
{
    if (!str)
        return 0;
    int plusIndex = -1;
    int equalIndex = -1;
    int i = 0;
    while (str[i] != '\0') 
    {
        if (str[i] == '+') 
            plusIndex = i;
        else if (str[i] == '=') 
            equalIndex = i;
        if (plusIndex != -1 && equalIndex != -1) 
            break;
        i++;
    }
    if (plusIndex != -1 && equalIndex != -1) 
        return plusIndex < equalIndex;
    return 0;
}







int hasPlusEqual(char *str)
{
    int i = 0;
    while (str[i] != '\0') 
    {
        if (str[i] == '+' && str[i + 1] == '=')
        {
            return 1;
        }
        i++;
    }
    return 0; 
}

















void print_export(t_environment_list *envp, int assigned_val)  //no arg only export (PRINTING EXPORT LIST)
{
    t_environment_list *env = envp;

    int count = 0;
    t_environment_list *current = env;
    while (current != NULL)
    {
        count++;
        current = current->next;
    } 

    t_environment_list **nodes = (t_environment_list **)malloc(count * sizeof(t_environment_list *));
    if (nodes == NULL)
        return;

    current = env;
    int index = 0;
    while (current != NULL)
     {
        nodes[index++] = current;
        current = current->next;
    }

    for (int i = 0; i < count - 1; i++)
     {
        int min_idx = i;
        for (int j = i + 1; j < count; j++)
         {
            if (strcmp(nodes[j]->name_and_value[0], nodes[min_idx]->name_and_value[0]) < 0) 
                min_idx = j;
        }
        if (min_idx != i) 
        {
            t_environment_list *temp = nodes[i];
            nodes[i] = nodes[min_idx];
            nodes[min_idx] = temp;
        }
    }

    for (int i = 0; i < count; i++)
     {
        if (nodes[i]->envp_flag == 1 || assigned_val) 
                printf("declare -x %s=\"%s\"\n", nodes[i]->name_and_value[0], nodes[i]->name_and_value[1]);
        else if (nodes[i]->envp_flag == 0)
            printf("declare -x %s\n", nodes[i]->name_and_value[0]);
    }

    free(nodes);
}




char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i = 0;
    if (!src || !(*src))
        return NULL;
   while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		++i;
	}
	return (dest);
}





int	ft_isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') )
		return (1);
	return (0);
}







int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}




// size_t get_index_of_char(const char *str, char c)
// {
//     size_t len = 0;
//     while (str[len] != '\0' && str[len] != c)
//         len++;
//     return len;
// }


// int findEqualChar(const char *text)
// {
//     if (!text || !(*text))
//         return 0;
//     while (*text != '\0')
//     {
//         if (*text == '=') 
//             return 1;
//         text++;
//     }
//     return 0;
// }



