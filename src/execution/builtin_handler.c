/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:47:50 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/18 19:26:22 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	which_builtin(t_minishell *shell, t_cmd *cmd);

void	builtin(t_minishell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		last_return;

	cmd->argv = expand_argv(shell, cmd->argv);
	if (!shell->lstfd)
		which_builtin(shell, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			exit_code(shell, errno);
		if (pid == 0)
		{
			which_builtin(shell, cmd);
			last_return = shell->lst_pid->rbuiltin;
			gc_free_all(shell->gc);
			exit(last_return << 8);
		}
		else
			pid_add(shell, pid, FORKED, FORKED);
	}
}

static void	which_builtin(t_minishell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		echo_builtin(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		cd_builtin(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		exit_builtin(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		export_builtin(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		unset_builtin(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		pwd_builtin(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		env_builtin(shell, cmd);
}
