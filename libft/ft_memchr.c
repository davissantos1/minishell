/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:34:31 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/22 20:31:15 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	uc;	

	i = 0;
	ptr = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == uc)
			return ((void *)&ptr[i]);
		i++;
	}
	return ((void *)0);
}
