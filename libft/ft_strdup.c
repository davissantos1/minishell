/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:35:40 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/13 21:33:51 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_malloc;
	size_t	i;	

	i = 0;
	s_malloc = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (s_malloc == (void *)0)
		return ((void *)0);
	while (s[i])
	{
		s_malloc[i] = s[i];
		i++;
	}
	s_malloc[i] = '\0';
	return (s_malloc);
}
