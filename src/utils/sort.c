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

static int	ft_strcmp_alpha(const char *s1, const char *s2);
static void	alpha_order(char **tab, int i, int j);
static void	ascii_order(char **tab, int i, int j);

void	sort_table(char **table, int order)
{
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
			if (order)
				alpha_order(table, i, j);
			else
				ascii_order(table, i, j);
			j++;
		}
		i++;
	}
}

static void	alpha_order(char **tab, int i, int j)
{
	char	*tmp;

	if (ft_strcmp_alpha(tab[i], tab[j]) > 0)
	{
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
	}
}

static int	ft_strcmp_alpha(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while ((ft_tolower(s1[index]) || ft_tolower(s2[index])))
	{
		if (ft_tolower(s1[index]) != ft_tolower(s2[index]))
			return (ft_tolower(s1[index]) - ft_tolower(s2[index]));
		index++;
	}
	return (0);
}

static void	ascii_order(char **tab, int i, int j)
{
	char	*tmp;

	if (ft_strcmp(tab[i], tab[j]) > 0)
	{
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
	}
}