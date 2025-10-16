/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:54:25 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/16 19:19:22 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_minishell *s, char *var)
{
	int		index;
	char	*result;

	index = 0;
	while (s->env[index])
	{
		if (!ft_strncmp(s->env[index], var, ft_strlen(var) + 1))
		{
			result = s->env + ft_strlen(var) + 2;
			return (result);
		}
		index++;
	}
	return (NULL);
}
