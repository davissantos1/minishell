/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:20:59 by dasimoes          #+#    #+#             */
/*   Updated: 2025/08/12 22:07:30 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxdup(char **mtx)
{
	int		i;
	int		size;
	char	**mtx_dup;

	i = -1;
	size = ft_mtxlen(mtx);
	mtx_dup = ft_calloc((size + 1), sizeof(char *));
	if (!mtx_dup)
		return (NULL);
	while (mtx[++i])
	{
		mtx_dup[i] = ft_strdup(mtx[i]);
		if (!mtx_dup[i])
			return (ft_mtxfree(mtx_dup));
	}
	return (mtx_dup);
}
