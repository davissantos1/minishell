/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:47:50 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 16:44:15 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_minishell *shell, t_cmd *cmd)
{
	func	builtins[7];
	pid_t	pid;
	int		last_return;

	cmd->argv = expand_argv(shell, cmd->argv);
	if (!shell->lstfd)
		builtins[cmd->is_builtin] (shell, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			exit_code(shell, errno);
		if (pid == 0)
		{
			builtins[cmd->is_builtin] (shell, cmd);
			last_return = shell->lst_pid->rbuiltin;
			gc_free_all(shell->gc);
			exit(last_return << 8);
		}
		else
			pid_add(shell, pid, FORKED, FORKED);
	}
}

static void	fill_functions(func *functions)
{
	functions[0] = echo_builtin;
	functions[1] = cd_builtin;
	functions[2] = exit_builtin;
	functions[3] = export_builtin;
	functions[4] = unset_builtin;
	functions[5] = pwd_builtin;
	functions[6] = env_builtin;
}
