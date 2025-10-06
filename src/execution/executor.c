/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:48:35 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/01 09:50:50 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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