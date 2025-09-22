/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:47:52 by dasimoes          #+#    #+#             */
/*   Updated: 2025/08/05 16:29:36 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	t_btree	*head;

	head = root;
	if (!head)
		return ;
	btree_apply_suffix((head->left), applyf);
	btree_apply_suffix((head->right), applyf);
	applyf(head->item);
}
