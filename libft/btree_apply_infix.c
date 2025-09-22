/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:48:02 by dasimoes          #+#    #+#             */
/*   Updated: 2025/08/05 16:19:17 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	t_btree	*head;

	head = root;
	if (!head)
		return ;
	btree_apply_infix((head->left), applyf);
	applyf(head->item);
	btree_apply_infix((head->right), applyf);
}
