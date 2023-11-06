#include "lib_for_minishell.h"



char	*ft_strncpy(char *dest, char *src, unsigned int n);
void extractNameAndValue(char *String, char **name, char **value);
int	ft_isalpha(int ch);
void print_export(t_environment_list *envp);
int	ft_isalnum(int c);
size_t get_index_of_char(const char *str, char c);
int findEqualChar(const char *text);




//add_new_node at the_end of_list
t_environment_list *ft_list_new_for_export(char *string_from_envp)
{
    t_environment_list *result = (t_environment_list *)malloc(sizeof(t_environment_list));

    if (!result)
        return NULL;
    size_t equal_index = get_index_of_char(string_from_envp, '=');
    result->name_and_value = (char **)malloc(2 * sizeof(char *));
    if (!result->name_and_value)
    {
        free(result);
        return NULL;
    }
    result->name_and_value[0] = (char *)malloc((equal_index + 1) * sizeof(char));
    result->name_and_value[1] = ft_strdup(string_from_envp + equal_index + 1);
    if (!result->name_and_value[0] || !result->name_and_value[1])
    {
        free(result->name_and_value[0]);
        free(result->name_and_value[1]);
        free(result->name_and_value);
        free(result);
        return NULL;
    }
    ft_strncpy(result->name_and_value[0], string_from_envp, equal_index);
    result->name_and_value[0][equal_index] = '\0';
    result->next = NULL;
    return result;
}



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

//example AAAAA=dadadada name = AAAA value = dadadada
void extractNameAndValue(char *String, char **name, char **value)
{
    char *equalSignPos = ft_strchr(String, '=');


    if (equalSignPos != NULL)
    {
        int nameLength = equalSignPos - String;
        int valueLength = ft_strlen(String) - nameLength - 1;
        *name = (char *)malloc((nameLength + 1) * sizeof(char));
        *value = (char *)malloc((valueLength + 1) * sizeof(char));
        if (*name && *value)
        {
            ft_strncpy(*name, String, nameLength);
            (*name)[nameLength] = '\0';
            ft_strncpy(*value, equalSignPos + 1, valueLength);
            (*value)[valueLength] = '\0';
        } 
        else
        {
            printf("Memory allocation failed.\n");
            *name = NULL;
            *value = NULL;
        }
    } 
    else
    {
        *name = String;
        *value = NULL;
    }

}

t_environment_list *set_last_node(t_environment_list **envp, int flag)  //setting flag
{
    if (*envp == NULL) 
        return NULL; 

    t_environment_list *current = *envp;

    while (current->next != NULL) 
        current = current->next;

    current->env_flag = flag;
    return current;
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

int wrong_name(char *str, char *name)
{
    //(void)str;
    printf("%s\n", name);
  
    if (!(name[0] == '_' ||  ft_isalpha(name[0])))
    {
       // printf("HERE\n");
             printf("minishell: export: `%s': not a valid identifier\n", str);
        return 1;
    }
    int len = ft_strlen(name);
    int i = 0;

    while (i < len)
    {
        if (!(ft_isalnum(name[i]) || name[i] == '_' || hasPlusEqual(str))) 
        {
            //printf("ERROR\n");
            printf("minishell: export: `%s': not a valid identifier\n", name);
            return 1;
        }
        i++;
    }

    return 0;
}



void ft_export(char **str, t_environment_list **envp)
{
    int i = 0;   //tokenneri vrayov ancnelu hamar
   
    if (!str || !(*str) || !streq(str[i], "export"))  //ete datarka kam export chi (IF NOT EXPORT DO NOTHING)
        return;

    while (str[i])     
    {
        if (i == 0 && streq(str[i], "export")) //ete arajiny exporta skip (SKIPPING EXPORT)
            i++;
        if (!str[i])            //ete export aranc argumentneri  //tpel export listy
        { 
            print_export(*envp);   //no arg only export (PRINTING EXPORT LIST)
            break;
        }
        char *name;
        char *value;
        extractNameAndValue(str[i], &name, &value);   //NAME AND VAL BY FIRST =
        if (wrong_name(str[i], name))   //CHECKING NAME 
        {
            if (str[i + 1])  //NOT LAST SKIP
                 i++;
                else
                    break;  //IF LAST ONE STOP
        }
            t_environment_list *newNode = ft_list_new_for_export(str[i]);  //nor listi ptr (CREATING NEW LIST)
            t_environment_list *current = *envp;  
            //+= case 
            
            while (current != NULL) // ITEARETION (ADDING NODES WITH FLAGS AND SETTING FLAGS TO PRINT)
            {
                if (streq(current->name_and_value[0], name))  //ete arden ka ed anunov node (OLD VALUE WITH =)
                {
                      if (findEqualChar(str[i]))
                      {
                            printf("CASE 1 (old value with =) value [%s]\nenv_list\n)  [%s]\n\n", str[i], value);
                            current->name_and_value[1] = value;
                            set_last_node(envp, 1);              //WILL BE SHOWN IN ENV
                      }
                    else    
                    {
                          printf("CASE 2 (old value without =) value [%s])  [%s]\nexport_list\n", str[i], value); //PLD VALUE WITHOUT =
                        set_last_node(envp, 0); //NOT SHOWN IN EXPORT
                    }
                   // free(current->name_and_value[1]);  //poxarinel arjeqy
                    break;
                    //free(name);
                }
                if (current->next == NULL)          //NEW VALUE
                { 
                    ft_list_add_back_for_environment(envp, newNode);  //ADD NODE
                    if (findEqualChar(str[i]) || (findEqualChar(str[i]) && str[i][0] == '\0') ) //NEW VAL WITH =
                    {
                          printf("CASE 3\n (new value with =) [%s]\nenv_list\n", str[i]);
                         set_last_node(envp, 1);
                    }
                    else
                    {
                        printf("CASE 4 (NEW value without =) [%s]\nexport_list\n", str[i]);  //NEW VAL WITHOUT =
                         set_last_node(envp, 0);
                    }
                    break ;
                }
                current = current->next;
            } 

            
         i++; 
     }
}



void print_export(t_environment_list *envp)
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
    while (current != NULL) {
        nodes[index++] = current;
        current = current->next;
    }

    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(nodes[j]->name_and_value[0], nodes[min_idx]->name_and_value[0]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            t_environment_list *temp = nodes[i];
            nodes[i] = nodes[min_idx];
            nodes[min_idx] = temp;
        }
    }

    for (int i = 0; i < count; i++) {
        if (nodes[i]->env_flag == 1) {
            printf("declare -x %s=\"%s\"\n", nodes[i]->name_and_value[0], nodes[i]->name_and_value[1]);
        } else if (nodes[i]->env_flag == 0) {
            printf("declare -x %s\n", nodes[i]->name_and_value[0]);
        }
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




size_t get_index_of_char(const char *str, char c)
{
    size_t len = 0;
    while (str[len] != '\0' && str[len] != c)
        len++;
    return len;
}


int findEqualChar(const char *text)
{
    if (!text || !(*text))
        return 0;
    while (*text != '\0')
    {
        if (*text == '=') 
            return 1;
        text++;
    }
    return 0;
}