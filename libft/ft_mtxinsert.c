/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:38:35 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/07 16:53:06 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxinsert(char **src, char **insert, int pos)
{
	int		i;
	int		j;
	int		size;
	char	**result;

	i = -1;
	j = 0;
	size = ft_mtxlen(src) + ft_mtxlen(insert) + 1;
	result = ft_calloc(size, sizeof(char *));
	if (!result)
		return (NULL);
	while (++i < pos)
		result[i] = ft_strdup(src[i]);
	while (insert[j])
		result[i++] = ft_strdup(insert[j++]);
	while (src[pos])
		result[i++] = ft_strdup(src[pos++]);
	return (result);
}
