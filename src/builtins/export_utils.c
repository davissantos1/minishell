/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:19:46 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/31 10:04:14 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_identifier_error(char *var, int *ret)
{
	*ret = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	nvalid(char *var, int *ret)
{
	size_t	i;

	if (!var[0] || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (invalid_identifier_error(var, ret));
	if (var[0] == '_' && (var[1] == '=' || var[1] == '+'))
		return (invalid_identifier_error(var, ret));
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+')
		{
			if (var[i + 1] == '=')
				break ;
			else
				return (invalid_identifier_error(var, ret));
		}
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (invalid_identifier_error(var, ret));
		i++;
	}
	return (0);
}

void	remove_plus(char *var, char *cpy_var)
{
	size_t	var_len;

	var_len = ft_strlen(var);
	ft_memmove(cpy_var + var_len, cpy_var + var_len + 1,
		ft_strlen(cpy_var + var_len));
}

void	print_mtx(char **mtx, int fd)
{
	char	*equal;

	while (*mtx)
	{
		equal = ft_strchr(*mtx, '=');
		if (equal)
			*equal = '\0';
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(*mtx, fd);
		if (equal)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(equal + 1, fd);
			ft_putendl_fd("\"", fd);
			*equal = '=';
		}
		else
			ft_putchar_fd('\n', fd);
		mtx++;
	}
}
