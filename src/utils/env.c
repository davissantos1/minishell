/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:54:25 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/01 10:28:38 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **env, char *var)
{
	int		index;
	char	*equal;

	index = 0;
	while (env[index])
	{
		equal = ft_strchr(env[index], '=');
		if (equal)
			*equal = '\0';
		if (!ft_strcmp(env[index], var))
		{
			if (equal)
				*equal = '=';
			return (equal + 1);
		}
		if (equal)
			*equal = '=';
		index++;
	}
	return (NULL);
}
