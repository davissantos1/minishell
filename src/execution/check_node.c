/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:10:52 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/01 14:13:15 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_node(t_minishell *shell, t_ast *node)
{
	if (node->type == NODE_CMD)
		return (executor(node));
	else if (node->type == NODE_PIPE)
		return(pipe_node(shell, node));
	else if (node->type == NODE_AND)
		return (and_node(shell, node));
	else
		return (or_node(shell, node));
}
