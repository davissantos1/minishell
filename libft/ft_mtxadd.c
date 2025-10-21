/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:05:05 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 17:41:08 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtxadd(char **mtx, char *s)
{
	char	**new_mtx;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_mtxlen(mtx);
	new_mtx = ft_calloc(len + 2, sizeof(char *));
	if (!new_mtx)
		return (NULL);
	while (mtx[i])
	{
		new_mtx[i] = mtx[i];
		i++;
	}
	new_mtx[i] = s;
	return (new_mtx);
}
