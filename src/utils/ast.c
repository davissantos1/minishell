/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:43:00 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/12 18:33:13 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_flip(t_ast **root)
{
	t_ast	*cur;
	t_ast	*tmp;

	if (!*root || !root)
		return ;
	if (!(*root)->right && !(*root)->left)
		return ;
	cur = *root;
	tmp = cur->left;
	tmp->right = cur->right;
	tmp->left = cur;
	cur->right = NULL;
	cur->left = NULL;
	*root = tmp;
	ast_flip(&(*root)->right);
}

//int	ast_validate(t_ast *root)
//{
//	
//
//}
