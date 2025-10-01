/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:30:36 by vitosant          #+#    #+#             */
/*   Updated: 2025/09/30 11:40:11 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static t_cmd *get_cmd_node(t_ast *node, int	dir);

void	pipe_node(t_minishell *shell, t_ast *node)
{
	int		pipe_fd[2];
	t_cmd	*left_cmd;
	t_cmd	*right_cmd;

	if(pipe(pipe_fd) == -1)
		return (exit_code(shell, errno));
	right_cmd = get_cmd_node(node, RIGHT);
	left_cmd = get_cmd_node(node, LEFT);
	left_cmd->std_out = pipe_fd[1];
	right_cmd->std_in = pipe_fd[0];
	handler(shell, node->left);
	handler(shell, node->right);
	close_pipes(pipe_fd);
}

static t_cmd *get_cmd_node(t_ast *node, int	dir)
{
	while (node->type != NODE_CMD)
	{
		if (dir == LEFT)
		{
			node = node->left;
			dir = RIGHT;
		}
		else
		{
			node = node->right;
			dir = LEFT;
		}
	}
	return (node->data);
}
