/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:45:20 by dasimoes          #+#    #+#             */
/*   Updated: 2025/07/22 20:16:03 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	max;

	max = (size_t) -1;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > max / size)
		return ((void *)0);
	result = malloc(nmemb * size);
	if (result == (void *)0)
		return ((void *)0);
	ft_bzero(result, nmemb * size);
	return (result);
}
