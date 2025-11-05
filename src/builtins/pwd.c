/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:06:54 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/31 08:35:16 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_minishell *shell, t_cmd *cmd)
{
	char	cwd[PATH_MAX];
	int		fd;

	fd = 1;
	if (!shell->lstfd)
		fd = cmd->std_out;
	ft_bzero(cwd, PATH_MAX);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd");
		pid_add(shell, NOT_FORKED, NOT_FORKED, errno << 8);
		close_redir(shell, cmd);
		return ;
	}
	ft_putendl_fd(cwd, fd);
	close_redir(shell, cmd);
	pid_add(shell, NOT_FORKED, NOT_FORKED, 0);
}
