/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:47:50 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/30 12:20:30 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_functions(func *functions);
static void	child_process(t_minishell *shell, t_cmd *cmd, func	builtins[7]);

void	builtin(t_minishell *shell, t_cmd *cmd)
{
	func	builtins[7];
	pid_t	pid;

	fill_functions(builtins);
	if (!shell->lstfd)
		builtins[cmd->is_builtin](shell, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			exit_code(shell, errno);
		if (pid == 0)
			child_process(shell, cmd, builtins);
		else
			pid_add(shell, pid, FORKED, FORKED);
	}
}

static void	child_process(t_minishell *shell, t_cmd *cmd, func	builtins[7])
{
	int		last_return;

	if (cmd->std_in != STDIN_FILENO)
		dup2(cmd->std_in, STDIN_FILENO);
	if (cmd->std_out != STDOUT_FILENO)
		dup2(cmd->std_out, STDOUT_FILENO);
	close_fdlst(shell->lstfd);
	close_redir(shell, cmd);
	builtins[cmd->is_builtin](shell, cmd);
	last_return = shell->lst_pid->rbuiltin;
	gc_free_all(shell->gc);
	exit(last_return << 8);
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
