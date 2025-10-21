/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 09:16:20 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/21 17:11:52 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_reverse_split(char **tab, char c)
{
	char	*str;
	size_t	tab_index;
	size_t	str_len;
	size_t	str_position;

	tab_index = 0;
	str_len = 0;
	while (tab[tab_index])
	{
		str_len += ft_strlen(tab[tab_index]);
		tab_index++;
	}
	str_len += ((c > 0) * tab_index) + 1;
	str = ft_calloc(str_len, 1);
	if (!str)
		return (NULL);
	tab_index = 0;
	while (tab[tab_index])
	{
		str_position = ft_strlcat(str, tab[tab_index], str_len);
		if (c && tab[tab_index + 1])
			str[str_position] = c;
		tab_index++;
	}
	return (str);
}
