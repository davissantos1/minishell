/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:25:10 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/25 21:50:41 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxndup(char **mtx, size_t n)
{
	size_t	i;
	char	**mtx_dup;

	i = 0;
	mtx_dup = ft_calloc((n + 1), sizeof(char *));
	if (!mtx_dup)
		return (NULL);
	while (i < n)
	{
		mtx_dup[i] = ft_strdup(mtx[i]);
		if (!mtx_dup[i])
			return (ft_mtxfree(mtx_dup));
		i++;
	}
	return (mtx_dup);
}
