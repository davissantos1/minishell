/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:27:31 by dasimoes          #+#    #+#             */
/*   Updated: 2025/08/29 22:27:56 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gc_addptr(void *p, t_gc *gc, t_gc_tag tag)
{
	t_gc_node	*node;

	if (!p || gc_findptr(p, gc))
		return (p);
	node = gc_create_node(p);
	if (!node)
		return (NULL);
	if (!gc->lists[tag])
		gc->lists[tag] = node;
	else
	{
		node->next = gc->lists[tag];
		gc->lists[tag] = node;
	}
	return (p);
}

void	*gc_addmtx(void *mtx, t_gc *gc, t_gc_tag tag)
{
	char	**matrix;
	void	*temp;
	int		index;

	index = 0;
	matrix = (char **)mtx;
	if (!gc_addptr(mtx, gc, tag))
		return (NULL);
	while (matrix[index])
	{
		temp = gc_addptr(matrix[index], gc, tag);
		if (!temp)
		{
			while (index > 0)
			{
				index--;
				gc_delptr(matrix[index], gc, tag);
			}
			gc_delptr(matrix, gc, tag);
			return (NULL);
		}
		index++;
	}
	return (mtx);
}

void	*gc_addlst(void *head, t_gc *gc, t_gc_tag tag)
{
	t_list	*list;
	int		index;		

	list = (t_list *)head;
	index = 0;
	while (list)
	{
		if (!gc_addptr(list, gc, tag))
		{
			gc_dellst(head, index, gc, tag);
			return (NULL);
		}
		if (list->content)
		{
			if (!gc_addptr(list->content, gc, tag))
			{
				gc_dellst(head, index + 1, gc, tag);
				return (NULL);
			}
		}
		list = list->next;
		index++;
	}
	return (head);
}

void	*gc_addbtree(void *root, t_gc *gc, t_gc_tag tag)
{
	t_btree	*node;

	node = (t_btree *)root;
	if (!node)
		return (NULL);
	if (!gc_addptr(node, gc, tag))
		return (NULL);
	if (node->item)
	{
		if (!gc_addptr(node->item, gc, tag))
			return (gc_delbtree(root, gc, tag), NULL);
	}
	if (node->left)
	{
		if (!gc_addbtree(node->left, gc, tag))
			return (gc_delbtree(root, gc, tag), NULL);
	}
	if (node->right)
	{
		if (!gc_addbtree(node->right, gc, tag))
			return (gc_delbtree(root, gc, tag), NULL);
	}
	return (root);
}
