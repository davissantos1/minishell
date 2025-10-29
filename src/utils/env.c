/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:54:25 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/28 20:02:53 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_minishell *s, char *var)
{
	int		index;
	int		len;
	char	*result;

	index = 0;
	len = ft_strlen(var);
	while (s->env[index])
	{
		
		if (!ft_strncmp(s->env[index], var, len))
		{
			if (s->env[index][len] == '=')
			{
				result = s->env[index] + len + 2;
				return (result);
			}
		}
		index++;
	}
	return (NULL);
}
