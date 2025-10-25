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

char	*get_env(char **env, char *var)
{
	int		index;
	int		len;
	char	*result;

	index = 0;
	len = ft_strlen(var);
	while (env[index])
	{
		if (!ft_strncmp(env[index], var, len))
		{
			result = env[index] + len + 1;
			return (result);
		}
		index++;
	}
	return (NULL);
}
