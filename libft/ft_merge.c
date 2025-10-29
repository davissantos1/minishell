/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:52:25 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/29 13:00:23 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_merge(char **mtx)
{
	char	*res;
	char	*tmp;
	int		index;

	index = 1;
	if (!mtx[1])
		return (ft_strdup(mtx[0]));
	res = ft_strdup(mtx[0]);
	while (mtx[index])
	{
		tmp = res;
		res = ft_strjoin(res, mtx[index]);
		if (!res)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		index++;
	}
	return (res);
}
