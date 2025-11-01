/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:58:36 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/01 20:00:35 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_table(char **table)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	len = ft_mtxlen(table);
	i = 0;
	j = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(table[i], table[j]) > 0)
			{
				tmp = table[i];
				table[i] = table[j];
				table[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
