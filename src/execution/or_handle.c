/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:34:14 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/13 17:24:21 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	or_node(t_minishell *shell, t_ast *node)
{
	int	grepper;

	executor(shell, node->left);
	grepper = last_return(shell);
	shell->exit = grepper;
	if (grepper != 0)
		executor(shell, node->right);
}
