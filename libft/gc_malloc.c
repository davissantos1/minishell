/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:15:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/14 13:11:23 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gc_node	*gc_create_node(void *p)
{
	t_gc_node	*node;

	node = malloc(sizeof(t_gc_node));
	if (!node)
		return (NULL);
	node->ptr = p;
	node->next = NULL;
	return (node);
}

t_gc	*gc_init(void)
{
	t_gc	*gc;
	int		i;

	i = 0;
	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	while (i < GC_COUNT)
	{
		gc->lists[i] = NULL;
		i++;
	}
	return (gc);
}

void	*gc_malloc(size_t size, t_gc *gc, t_gc_tag tag)
{
	t_gc_node	*node;
	void		*p;

	if (size == 0 || tag >= GC_COUNT)
		return (NULL);
	p = malloc(size);
	if (!p)
		return (NULL);
	node = gc_create_node(p);
	if (!node)
		return (ft_free(p));
	if (!gc->lists[tag])
		gc->lists[tag] = node;
	else
	{
		node->next = gc->lists[tag];
		gc->lists[tag] = node;
	}
	return (p);
}

void	*gc_calloc(size_t size, t_gc *gc, t_gc_tag tag)
{
	t_gc_node	*node;
	void		*p;

	if (size == 0 || tag >= GC_COUNT)
		return (NULL);
	p = ft_calloc(size, 1);
	if (!p)
		return (NULL);
	node = gc_create_node(p);
	if (!node)
		return (ft_free(p));
	if (!gc->lists[tag])
		gc->lists[tag] = node;
	else
	{
		node->next = gc->lists[tag];
		gc->lists[tag] = node;
	}
	return (p);
}

void	*gc_realloc(void *p, size_t old_size, size_t new_size, t_gc *gc)
{
	int		tag;
	void	*new;

	tag = gc_findtag(p, gc);
	if (tag == -1)
		return (NULL);
	new = gc_calloc(new_size, gc, tag);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, p, old_size);
	gc_free_ptr(p, gc);
	return (new);
}
