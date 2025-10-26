/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_break.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:28:37 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/25 21:54:47 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_break(char *str, size_t index)
{
	char	**res;
	char	tmp;

	res = ft_calloc(sizeof(char *), 2);
	if (index > ft_strlen(str) || !res)
		return (NULL);
	tmp = str[index];
	str[index] = '\0';
	res[0] = ft_strdup(str);
	str[index] = tmp;
	res[1] = ft_strdup(str + index);
	if (!res[0] || !res[1])
		return (NULL);
	return (res);
}
