/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:38:24 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/14 13:02:43 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gc_free_tag(t_gc *gc, t_gc_tag tag)
{
	t_gc_node	*tmp;
	t_gc_node	*current;

	if (!gc || tag >= GC_COUNT)
		return (NULL);
	current = gc->lists[tag];
	while (current)
	{
		tmp = current->next;
		ft_free(current->ptr);
		ft_free(current);
		current = tmp;
	}
	gc->lists[tag] = NULL;
	return (NULL);
}

void	*gc_free_all(t_gc *gc)
{
	int			i;

	i = 0;
	if (!gc)
		return (NULL);
	while (i < GC_COUNT)
		gc_free_tag(gc, i++);
	ft_free(gc);
	return (NULL);
}

void	*gc_free_ptr(void *p, t_gc *gc)
{
	t_gc_tag	tag;

	tag = gc_findtag(p, gc);
	gc_delptr(p, gc, tag);
	ft_free(p);
	return (NULL);
}
