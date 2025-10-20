/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:44:54 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 17:01:38 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	disco(t_minishell *shell, char *dir);

void	cd_builtin(t_minishell *shell, t_cmd *cmd)
{
	if (!cmd->argv[1])
	{
		pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
		return ;
	}
	else if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("cd: Too many arguments", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
		return ;
	}
	disco(shell, cmd->argv[1]);
}

static void	disco(t_minishell *shell, char *dir)
{
	if (chdir(dir) == -1)
	{
		perror("cd");
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
	}
	else
		pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}
