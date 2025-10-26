/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 11:19:46 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/25 13:31:01 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nvalid(char *var, int *ret)
{
	char	*equal;

	equal = ft_strchr(var, '=');
	if (!ft_isalpha(*var) || (equal && !ft_isalpha(*(equal - 1))
		&& *(equal - 1) != '+'))
	{
		*ret = 1;
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (1);
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
