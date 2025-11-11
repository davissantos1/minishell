/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:30:36 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/11 07:57:19 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_cmd_node(t_minishell *shell, t_ast *node, int *fd, char flag);
static void	add_fdlst(t_minishell *shell, int fd);
static void	*is_redir(t_cmd *cmd, char flag);
static void	close_pipes(t_minishell *shell);

void	pipe_node(t_minishell *shell, t_ast *node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	add_fdlst(shell, pipe_fd[0]);
	add_fdlst(shell, pipe_fd[1]);
	set_cmd_node(shell, node->left, pipe_fd, STDOUT_FD);
	set_cmd_node(shell, node->right, pipe_fd, STDIN_FD);
	executor(shell, node->left);
	executor(shell, node->right);
	close_pipes(shell);
}

static void	set_cmd_node(t_minishell *shell, t_ast *node, int *fd, char flag)
{
	t_cmd	*cmd;

	if (!node)
		return ;
	if (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
	{
		cmd = node->data;
		if (flag == STDIN_FD && !is_redir(cmd, flag))
			cmd->std_in = fd[0];
		else if (flag == STDOUT_FD && !is_redir(cmd, flag))
			cmd->std_out = fd[1];
	}
	if (node->left)
		set_cmd_node(shell, node->left, fd, flag);
	if (node->right)
		set_cmd_node(shell, node->right, fd, flag);
}

static void	add_fdlst(t_minishell *shell, int fd)
{
	t_lstint	*node;

	node = gc_calloc(sizeof(t_lstint), shell->gc, GC_FDLIST);
	if (!node)
		exit_code(shell, errno);
	node->value = fd;
	node->next = shell->lstfd;
	shell->lstfd = node;
}

static void	close_pipes(t_minishell *shell)
{
	t_lstint	*lst;

	lst = shell->lstfd;
	close(lst->value);
	lst = lst->next;
	close(lst->value);
	shell->lstfd = lst->next;
}

static void	*is_redir(t_cmd *cmd, char flag)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (flag == STDOUT_FD && redir)
	{
		if (redir->type == APPEND || redir->type == REDOUT)
			return (redir);
		redir = redir->next;
	}
	while (flag == STDIN_FD && redir)
	{
		if (redir->type == HEREDOC || redir->type == REDIN)
			return (redir);
		redir = redir->next;
	}
	return (NULL);
}
