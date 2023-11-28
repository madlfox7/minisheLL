
#include "lib_for_minishell.h"

int	ft_atoi(const char	*str)
{
	int				num;
	int				minus;

	num = 0;
	minus = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-')
	{
		minus *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
		str++;
	}
	return (num * minus);
}
