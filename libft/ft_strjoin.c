/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:32:53 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/18 21:10:20 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	total_size;

	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(total_size * sizeof(char));
	if (result == ((void *)0))
		return ((void *)0);
	ft_strlcpy(result, s1, total_size);
	ft_strlcat(result, s2, total_size);
	return (result);
}
