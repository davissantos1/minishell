/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:48:35 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/11 17:14:05 by vitosant         ###   ########.fr       */
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
	if (cmd->std_in < 0 || cmd->std_out < 0 || !check_command(cmd))
		return ;
	if (cmd->is_builtin)
		return (builtin(shell, cmd));
	pid = fork();
	if (pid == -1)
		exit_code(shell, errno);
	if (pid == 0)
		exec_program(shell, cmd);
	pid_add(shell, pid, NOT_BUILTIN, NOT_BUILTIN);
}

static void	exec_program(t_minishell *shell, t_cmd *cmd)
{
	char		**argv;
	char		**env;
	t_lstint	*node_fd;

	argv = ft_mtxdup(cmd->argv);
	node_fd = cmd->lst_fds;
	env = shell->env;
	if (!argv)
		exit_code(shell, errno);
	if (cmd->std_in != 0 && dup2(cmd->std_in, STDIN_FILENO) == -1)
		perror("dup2");
	if (cmd->std_out != 1 && dup2(cmd->std_out, STDOUT_FILENO) == -1)
		perror("dup2");
	close_redir(cmd);
	while (node_fd)
	{
		close(node_fd->value);
		node_fd = node_fd->next;
	}
	gc_free_all(shell->gc);
	execve(argv[0], argv, env);
	perror("execve");
	ft_mtxfree(argv);
	exit(errno);
}
