/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:11:02 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 18:09:24 by vitosant         ###   ########.fr       */
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
	if (ft_mtxfind((void **)mtx, (void *)s) == -1)
		return (mtx);
	new_mtx = ft_calloc(len, sizeof(char *));
	if (!new_mtx)
		return (NULL);
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
