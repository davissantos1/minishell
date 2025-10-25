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
	if (!ft_isalpha(*var))
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
	size_t	cpy_len;
	size_t	var_len;
	
	cpy_len = ft_strlen(cpy_var);
	var_len = ft_strlen(var);
	ft_memmove(cpy_var + var_len, cpy_var + var_len + 1,
		ft_strlen(cpy_var + var_len));
}
