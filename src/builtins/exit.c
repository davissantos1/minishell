/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:31:10 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/18 19:31:11 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_minishell *shell, t_cmd *cmd)
{
	int		ret;
	size_t	i;
	size_t	len;

	ret = 0;
	i = 0;
	if (cmd->argv[1] && ft_mtxlen(cmd->argv) == 2)
	{
		ret = 2;
		len = ft_strlen(cmd->argv[1]);
		while (ft_isdigit(cmd->argv[1][i]))
			i++;
		if (i == len)
			ret = (char) ft_atol(cmd->argv[1]);
		else
			ft_putstr_fd("exit: Requires numeric argument", 2);
	}
	else if (ft_mtxlen(cmd->argv) > 2)
	{
		ft_putstr_fd("exit: Too many arguments", 2);
		ret = 1;
	}
	gc_free_all(shell->gc);
	exit(ret);
}
