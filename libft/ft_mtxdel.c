/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:11:02 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/17 14:11:03 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxdel(char **mtx, char *s)
{
	char	**new_mtx;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_mtxlen(mtx);
	new_mtx = ft_calloc(len, sizeof(char));
	if (!new_mtx)
		return (NULL);
	if (ft_mtxfind(mtx, s) == -1)
		return (mtx);
	while (mtx[i])
	{
		if (mtx[i] != s)
		{
			new_mtx[j] = mtx[i];
			j++;
		}
		i++;
	}
	return (new_mtx);
}
