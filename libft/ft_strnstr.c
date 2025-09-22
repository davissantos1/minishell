/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:56:24 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/10 13:29:27 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && (i < len))
	{
		j = 0;
		while (little[j] && (i + j < len) && (big[i + j] == little[j]))
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return ((void *)0);
}
