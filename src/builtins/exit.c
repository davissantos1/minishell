/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:31:10 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 10:54:33 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_builtin(t_minishell *shell, t_cmd *cmd)
{
	int		ret;

	if (cmd->argv[1])
	{
		ft_putstr_fd("exit: Too many arguments", 2);
		ret = 1 << 8;
	}
	gc_free_all(shell->gc);
	exit(ret);
}
