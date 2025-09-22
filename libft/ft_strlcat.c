/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:52:22 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/09 21:55:17 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;
	size_t	size_dst;

	i = 0;
	size_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	if (size_dst >= size)
		return (size + size_src);
	while (src[i] && (i + size_dst < size - 1))
	{
		dst[i + size_dst] = src[i];
		i++;
	}
	dst[size_dst + i] = '\0';
	return (size_src + size_dst);
}
