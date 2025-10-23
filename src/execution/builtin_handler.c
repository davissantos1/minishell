/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:47:50 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/23 15:16:16 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_functions(func *functions);

void	builtin(t_minishell *shell, t_cmd *cmd)
{
	func	builtins[7];
	pid_t	pid;
	int		last_return;

	cmd->argv = expand_argv(shell, cmd->argv);
	fill_functions(builtins);
	if (cmd->std_out == 1)
		builtins[cmd->is_builtin] (shell, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			exit_code(shell, errno);
		if (pid == 0)
		{
			if (cmd->std_in != 0)
				dup2(cmd->std_in, 0);
			if (cmd->std_out != 1)
				dup2(cmd->std_in, 1);
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
