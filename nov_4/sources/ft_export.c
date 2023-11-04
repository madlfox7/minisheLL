#include "lib_for_minishell.h"



char	*ft_strncpy(char *dest, char *src, unsigned int n);
void extractNameAndValue(char *String, char **name, char **value);
int	ft_isalpha(int ch);
void print_export(t_environment_list *envp);


size_t get_index_of_char(const char *str, char c)
{
    size_t len = 0;
    while (str[len] != '\0' && str[len] != c)
        len++;
    return len;
}


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




void ft_export(char **str, t_environment_list **envp)
{
    int i = 0;

    if (!str || !(*str) || !streq(str[i], "export"))  //ete datarka kam export chi 
        return;

    while (str[i])     
    {
        if (i == 0 && streq(str[i], "export")) //ete arajiny exporta skip 
        {
            i++;
        }
        if (!str[i])            //ete export aranc argumentneri  //tpel export listy
        { 
            print_export(*envp);   
            break;
        }
        if (!ft_isalpha(str[i][0]) && str[i][0] != '#' && str[i][0] != '_')   //ete arajin tary Ascii-ov tar chi u comment chi error
        {
            printf("minishell: export: `%s': not a valid identifier\n", str[i]);
            break;
        }

        char *name;
        char *value;
        extractNameAndValue(str[i], &name, &value); //ktrel arajin = -ic araj u heton
        //petqa stugel anuni parsingy vor chtuylatrvac sym chlini u spacery???
        if (name && value)
        {
            //printf("\n\n name [%s]\nvalue[%s]\n\n", name, value);
            t_environment_list *newNode = ft_list_new_for_export(str[i]);  //nor listi ptr
            t_environment_list *current = *envp; 
            //+= case stugel 
            while (current != NULL)
            {
                if (streq(current->name_and_value[0], name))  //ete arden ka ed anunov node 
                {
                    free(current->name_and_value[1]);  //poxarinel arjeqy
                    current->name_and_value[1] = value;
                    free(name);
                    break;
                }
                if (current->next == NULL)
                { 
                    ft_list_add_back_for_environment(envp, newNode);  //ete chka avelacnel nor node
                    print_env(*envp);
                    break;
                }
                current = current->next;
            }
        } 
        else 
            printf("No '=' found in the string or memory allocation failed.\n");  //ete = chka avelacnel export list?
        i++;
    }
}


void print_export(t_environment_list *envp) // for export without options 
{
    t_environment_list *env = envp;
    //sort_env_list(env);

    t_environment_list *current = env;
    while (current != NULL)
    {
        printf("declare -x %s=\"%s\"\n", current->name_and_value[0], current->name_and_value[1]);
        current = current->next;
    }
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
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	return (0);
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
        *name = NULL;
        *value = NULL;
    }
}



