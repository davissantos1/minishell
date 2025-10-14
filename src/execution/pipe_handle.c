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
static void	add_fdlst(t_minishell *shell, int fd, t_cmd *cmd);

void	pipe_node(t_minishell *shell, t_ast *node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	set_cmd_node(shell, node->left, pipe_fd, STDOUT_FD);
	set_cmd_node(shell, node->right, pipe_fd, STDIN_FD);
	executor(shell, node->left);
	executor(shell, node->right);
	close_pipes(pipe_fd);
}

static void set_cmd_node(t_minishell *shell, t_ast *node, int *fd, char flag)
{
	t_cmd	*cmd;

	if (node->type == NODE_CMD)
	{
		cmd = node->data;
		if (flag == STDIN_FD)
			cmd->std_in = fd[0];
		else
			cmd->std_out = fd[1];
		add_fdlst(shell, fd[0], cmd);
		add_fdlst(shell, fd[1], cmd);
	}
	if (node->left)
		set_cmd_node(shell, node->left, fd, flag);
	if (node->right)
		set_cmd_node(shell, node->right, fd, flag);
}

static void	add_fdlst(t_minishell *shell, int fd, t_cmd *cmd)
{
	t_lstint	*node;

	node = gc_calloc(sizeof(t_lstint), shell->gc, GC_FDLIST);
	if (!node)
		exit_code(shell, errno);
	node->value = fd;
	node->next = cmd->lst_fds;
	cmd->lst_fds = node;
}
