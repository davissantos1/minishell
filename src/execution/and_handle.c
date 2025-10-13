/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:06:15 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 15:43:39 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	and_node(t_minishell *shell, t_ast *node)
{
	int	grepper;

	executor(shell, node->left);
	grepper = get_return(shell);
	shell->exit = grepper;
	if (grepper == 0)
		executor(shell, node->right);
}
