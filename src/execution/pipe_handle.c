/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:30:36 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/11 12:02:16 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_cmd_node(t_minishell *shell, t_ast *node, int *fd, char flag);
static void	add_fdlst(t_minishell *shell, int fd);
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

static void set_cmd_node(t_minishell *shell, t_ast *node, int *fd, char flag)
{
	t_cmd	*cmd;

	if (node->type == NODE_CMD)
	{
		cmd = node->data;
		if (flag == STDIN_FD && !cmd->redir)
			cmd->std_in = fd[0];
		else if (flag == STDOUT_FD)
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
	t_lstint *lst;

	lst = shell->lstfd;
	close(lst->value);
	lst = lst->next;
	close(lst->value);
	shell->lstfd = lst->next;
}
