/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:51:56 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/13 22:19:21 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		size;

	size = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *) &s[size]);
	while (size >= 0)
	{
		if ((unsigned char) s[size] == (unsigned char)c)
			return ((char *)&s[size]);
		size--;
	}
	return ((void *)0);
}
