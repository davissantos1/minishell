/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:53:02 by dasimoes          #+#    #+#             */
/*   Updated: 2025/08/14 19:53:22 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gc_findptr_tag(void *p, t_gc *gc, t_gc_tag tag)
{
	t_gc_node	*head;

	head = gc->lists[tag];
	while (head)
	{
		if (head->ptr == p)
			return (head->ptr);
		head = head->next;
	}
	return (NULL);
}

void	*gc_findptr(void *p, t_gc *gc)
{
	t_gc_node	*head;
	size_t		index;

	index = 0;
	head = gc->lists[index];
	while (index < GC_COUNT)
	{
		head = gc_findptr_tag(p, gc, index);
		if (head)
			return (head);
		index++;
	}
	return (NULL);
}

void	gc_delptr(void *p, t_gc *gc, t_gc_tag tag)
{
	t_gc_node	*head;
	t_gc_node	*prev;

	head = gc->lists[tag];
	prev = NULL;
	while (head)
	{
		if (head->ptr == p)
			break ;
		prev = head;
		head = head->next;
	}
	if (!head)
		return ;
	if (prev)
		prev->next = head->next;
	else
		gc->lists[tag] = head->next;
	free(head);
}

void	gc_dellst(void *head, int index, t_gc *gc, t_gc_tag tag)
{
	t_list	*list;

	list = (t_list *)head;
	while (index > 0)
	{
		if (list->content)
			gc_delptr(list->content, gc, tag);
		gc_delptr(list, gc, tag);
		index--;
		list = list->next;
	}
}

void	gc_delbtree(void *root, t_gc *gc, t_gc_tag tag)
{
	t_btree	*node;

	node = (t_btree *)root;
	if (!node)
		return ;
	gc_delbtree(node->left, gc, tag);
	gc_delbtree(node->right, gc, tag);
	if (node->item)
		gc_delptr(node->item, gc, tag);
	gc_delptr(node, gc, tag);
}
