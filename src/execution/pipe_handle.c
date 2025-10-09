/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:30:36 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/07 08:37:47 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void set_cmd_node(t_ast *node, int fd, char flag);

void	pipe_node(t_minishell *shell, t_ast *node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	set_cmd_node(node->left, pipe_fd[1], STDOUT_FD);
	set_cmd_node(node->right, pipe_fd[0], STDIN_FD);
	executor(shell, node->left);
	executor(shell, node->right);
	close_pipes(pipe_fd);
	if (shell->lst_pid)
		shell->exit = get_return(shell);
}

static void set_cmd_node(t_ast *node, int fd, char flag)
{
	t_cmd	*cmd;

	if (node->type == NODE_CMD)
	{
		cmd = node->data;
		if (flag == STDIN_FD)
			cmd->std_in = fd;
		else
			cmd->std_out = fd;
	}
	if (node->left)
		set_cmd_node(node->left, fd, flag);
	if (node->right)
		set_cmd_node(node->right, fd, flag);
}
