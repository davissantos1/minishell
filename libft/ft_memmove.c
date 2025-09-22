/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:36:40 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/22 20:39:58 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*pd;
	const unsigned char	*ps;

	i = 0;
	pd = (unsigned char *)dest;
	ps = (const unsigned char *)src;
	if (ps < pd)
	{
		while (n--)
			pd[n] = ps[n];
	}
	else
	{
		while (i < n)
		{
			pd[i] = ps[i];
			i++;
		}
	}
	return (dest);
}
