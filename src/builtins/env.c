/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:55:06 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/31 08:26:07 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_minishell *shell, t_cmd *cmd)
{
	char	**env;
	int		fd;

	fd = 1;
	if (!shell->lstfd)
		fd = cmd->std_in;
	env = shell->env;
	close_redir(shell, cmd);
	if (cmd->argv[1])
	{
		ft_putstr_fd("env: Too many arguments\n", 2);
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
		return ;
	}
	while (*env)
	{
		ft_putendl_fd(*env, fd);
		env++;
	}
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}
