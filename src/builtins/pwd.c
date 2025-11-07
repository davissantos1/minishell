/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:06:54 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/07 13:22:19 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_minishell *shell, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		fd;

	fd = cmd->std_out;
	if (shell->lstfd)
		fd = 1;
	ft_bzero(cwd, PATH_MAX);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd");
		pid_add(shell, NOT_FORKED, NOT_FORKED, errno << 8);
		close_redir(shell, cmd);
		return ;
	}
	ft_putendl_fd(cwd, fd);
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}
