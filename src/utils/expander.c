/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:35:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/28 23:38:14 by daviss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(t_minishell *s, char *var)
{
	char	*env_var;

	if (!var[1])
	{
		env_var = getenv("HOME");
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
	}
	if (var[1] == '-')
	{
		env_var = get_env(s, "OLDPWD");
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
	}
	if (var[1] == '+')
	{
		env_var = get_env(s, "PWD");
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
	}
	return (ft_strdup(var));
}

