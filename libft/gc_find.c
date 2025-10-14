/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:45:08 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/14 13:10:41 by dasimoes         ###   ########.fr       */
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

int	gc_findtag(void *p, t_gc *gc)
{
	t_gc_node	*head;
	size_t		index;

	index = 0;
	head = NULL;
	while (index < GC_COUNT)
	{
		head = gc_findptr_tag(p, gc, index);
		if (head)
			return (index);
		index++;
	}
	return (-1);
}
