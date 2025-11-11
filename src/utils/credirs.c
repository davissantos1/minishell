/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   credirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:10:56 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/11 17:11:26 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	credirs(t_minishell *shell, t_ast *node)
{
	if (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
		close_redir(shell, node->data);
	if (node->left)
		credirs(shell, node->left);
	if (node->right)
		credirs(shell, node->right);
}
