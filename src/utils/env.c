/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:54:25 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/25 10:12:44 by vitosant         ###   ########.fr       */
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
		if ((env[index][len] == '=' || !env[index][len])
			&& !ft_strncmp(env[index], var, len))
		{
			result = env[index] + len + 1;
			return (result);
		}
		index++;
	}
	return (NULL);
}
