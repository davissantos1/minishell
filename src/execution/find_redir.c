/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:18:46 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/04 14:24:24 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_redir(t_minishell *shell, t_ast *node)
{
	if (node->type == NODE_CMD)
		return (do_redir(shell, node->data));
	if (node->left && shell->exit != -130)
		find_redir(shell, node->left);
	if (node->right && shell->exit != -130)
		find_redir(shell, node->right);
}
