/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:48:35 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 10:27:31 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_exec(t_minishell *shell, t_cmd *cmd);
static void	exec_program(t_minishell *shell, t_cmd *cmd);

void	executor(t_minishell *shell, t_ast *node)
{
	if (node->type == NODE_CMD)
		try_exec(shell, node->data);
	else if (node->type == NODE_SUBSHELL)
		printf("subshell\n");
	else if (node->type == NODE_AND)
		and_node(shell, node);
	else if (node->type == NODE_OR)
		or_node(shell, node);
	else if (node->type == NODE_PIPE)
		pipe_node(shell, node);
}

static void	try_exec(t_minishell *shell, t_cmd *cmd)
{
	pid_t	pid;

	redirection(shell, cmd);
	find_path(shell, cmd);
	if (cmd->std_in < 0 || cmd->std_out < 0 || !check_command(cmd))
		return ;
	if (cmd->is_builtin)
	{
		builtin(shell, cmd);
		return ;
	}
	pid = fork();
	if (pid == -1)
		exit_code(shell, errno);
	if (pid == 0)
		exec_program(shell, cmd);
	pid_add(shell, pid, FORKED, FORKED);
	close_redir(shell, cmd);
}

static void	exec_program(t_minishell *shell, t_cmd *cmd)
{
	char		**argv;
	char		**env;

	argv = expand_argv(shell, cmd->argv);
	env = shell->env;
	if (!argv)
		exit_code(shell, errno);
	if (cmd->std_in != 0 && dup2(cmd->std_in, STDIN_FILENO) == -1)
		perror("dup2");
	if (cmd->std_out != 1 && dup2(cmd->std_out, STDOUT_FILENO) == -1)
		perror("dup2");
	close_redir(shell, cmd);
	close_fdlst(shell->lstfd);
	execve(argv[0], argv, env);
	perror("execve");
	gc_free_all(shell->gc);
	exit(errno);
}
