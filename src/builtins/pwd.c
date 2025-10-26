/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:06:54 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/21 14:17:50 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_minishell *shell, t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	ft_bzero(cwd, PATH_MAX);
	if (cmd->argv[1] || getcwd(cwd, PATH_MAX) == NULL)
	{
		if (cmd->argv[1])
			ft_putstr_fd("pwd: Too many arguments\n", 2);
		else
			perror("pwd");
		pid_add(shell, NOT_FORKED, NOT_FORKED, 1 << 8);
		return ;
	}
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}
