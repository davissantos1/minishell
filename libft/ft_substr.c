/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:07:06 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/22 22:58:04 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_substr_aux(char const *s, unsigned int start, size_t len)
{
	if (len > ft_strlen(s) - start)
		return (ft_strlen(s) - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_string;
	size_t	sub_size;

	i = 0;
	sub_size = ft_substr_aux(s, start, len);
	if (start >= ft_strlen(s))
	{
		sub_string = (char *)malloc(1 * sizeof(char));
		sub_string[0] = '\0';
		return (sub_string);
	}
	sub_string = (char *)malloc((sub_size + 1) * sizeof(char));
	if (sub_string == NULL)
		return (NULL);
	while (i < sub_size)
	{
		sub_string[i] = s[start + i];
		i++;
	}
	sub_string[i] = '\0';
	return (sub_string);
}
