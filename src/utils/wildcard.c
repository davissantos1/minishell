#include "minishell.h"

int	check_wildcard(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] != '*')
			return (0);
		index++;
	}
	return (1);
}

int	check_wildcard_str(char *str, char *match)
{
	int	index;

	index = 0;
	if (ft_strlen(str) != ft_strlen(match))
		return (0);
	while (str[index])
	{
		if (str[index] == '*')
			index++;
		else
		{
			if (str[index] != match[index])
				return (0);
			index++;
		}
	}
	return (1);
}
