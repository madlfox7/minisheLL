
#include "lib_for_minishell.h"

int	ft_isalpha(int ch);
int	ft_isalnum(int c);


void error_msg(char *name, char *str)
{
      if (ft_strchr(str, '='))
            printf("minishell: export: `%s': not a valid identifier\n", str);
        else
              printf("minishell: export: `%s': not a valid identifier\n", name);
}
int ft_wrong_name(char *name, char *str)
{
    int len;
    int i;

    if (!(name[0] == '_' ||  ft_isalpha(name[0])) || !name || !(*name) )
    {
          error_msg(name, str);
        return (1);
    }

    len = ft_strlen(name);
    i = 0;
    while (i < len)
    {
      if (!(ft_isalnum(name[i]) || name[i] == '_') )
        {
        error_msg(name, str);
            return (1);
        }
        i++;
    }
    return (0);
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
