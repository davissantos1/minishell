/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:34:14 by vitosant          #+#    #+#             */
/*   Updated: 2025/09/30 11:38:29 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	or_node(t_minishell *shell, t_ast *node)
{
	handler(shell, node->left);
	if (shell->exit != 0)
		handler(shell, node->right);
}