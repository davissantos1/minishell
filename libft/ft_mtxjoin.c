/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:10:43 by dasimoes          #+#    #+#             */
/*   Updated: 2025/08/12 22:06:42 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_mtxjoin_aux(char **mtx, char **mtx1, char **mtx2)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (mtx1[++i])
	{
		mtx[i] = ft_strdup(mtx1[i]);
		if (!mtx[i])
			return (ft_mtxfree(mtx));
	}
	while (mtx2[++j])
	{
		mtx[i] = ft_strdup(mtx2[j]);
		if (!mtx[i])
			return (ft_mtxfree(mtx));
		i++;
	}
	return (mtx);
}

char	**ft_mtxjoin(char **mtx1, char **mtx2)
{
	char	**mtx;
	int		size;

	size = ft_mtxlen(mtx1) + ft_mtxlen(mtx2);
	if (!*mtx1)
		return (ft_mtxdup(mtx2));
	if (!*mtx2)
		return (ft_mtxdup(mtx1));
	mtx = ft_calloc((size + 1), sizeof(char *));
	if (!mtx)
		return (NULL);
	mtx = ft_mtxjoin_aux(mtx, mtx1, mtx2);
	if (!mtx)
		return (NULL);
	return (mtx);
}
