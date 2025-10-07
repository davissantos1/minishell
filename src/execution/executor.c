/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:48:35 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/07 12:08:47 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_exec(t_minishell *shell, t_cmd *cmd);
static void	exec_program(t_minishell *shell, t_cmd *cmd);

void	executor(t_minishell *shell, t_ast *node)
{
	if (node->type == NODE_CMD)
		return (try_exec(shell, node->data));
	else if (node->type == NODE_SUBSHELL)
		subshell_module(shell, node);
	else if (node->type == NODE_AND)
		end_node(shell, node);
	else if (node->type == NODE_OR)
		or_node(shell, node);
	else if (node->type == NODE_PIPE)
		pipe_node(shell, node);
	if (node->left)
		executor(shell, node->left);
	if (node->right)
		executor(shell, node->right);
}

static void	try_exec(t_minishell *shell, t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->std_in == -256)
		cmd->std_in = shell->std_in;
	if (cmd->std_out == -256)
		cmd->std_out = shell->std_out;
	if (cmd->std_in < 0 || cmd->std_out < 0)
		return ;
	if (!check_command(cmd))
	{
		shell->exit = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
		exit_code(shell, errno);
	if (pid == 0)
		exec_program(shell, cmd);
	pid_add(shell, pid);
}

static void	exec_program(t_minishell *shell, t_cmd *cmd)
{
	if (dup2(cmd->std_in, STDIN_FILENO) == -1)
		perror("");
	if (dup2(cmd->std_out, STDOUT_FILENO) == -1)
		perror("");
	if (close(cmd->std_in) == -1)
		perror("");
	if (close(cmd->std_out) == -1)
		perror("");
	execve(cmd->argv[0], cmd->argv, shell->env);
	perror("");
	exit_code(shell, errno);
}