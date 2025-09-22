/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:47:27 by dasimoes          #+#    #+#             */
/*   Updated: 2025/08/05 16:18:49 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	t_btree	*head;

	head = root;
	if (!head)
		return ;
	applyf(head->item);
	btree_apply_prefix((head->left), applyf);
	btree_apply_prefix((head->right), applyf);
}
