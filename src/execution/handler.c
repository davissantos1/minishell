/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:14:39 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/01 13:42:03 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(t_minishell *shell, t_ast *node)
{
	if (node->type == NODE_CMD)
		executor(node);
	else if (node->type == NODE_PIPE)
		return(pipe_node(shell, node));
	else if (node->type == NODE_AND)
		return (and_node(shell, node));
	else
		return (or_node(shell, node));
	wait(&shell->exit);
	shell->exit = (shell->exit & 0xFF00 >> 8);
}
