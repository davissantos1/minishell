/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:35:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/29 20:01:21 by dasimoes         ###   ########.fr       */
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
	if (var[1] == '-' && (!var[2] || is_space(var[2])))
	{
		env_var = get_env(s, "OLDPWD");
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
	}
	if (var[1] == '+' && (!var[2] || is_space(var[2])))
	{
		env_var = get_env(s, "PWD");
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
	}
	return (ft_strdup(var));
}

char	*expand_special(t_minishell *s, char *var)
{
	if (var[0] == '~')
		return (expand_tilde(s, var));
	if (var[0] == '$')
	{
		if (is_space(var[1]) || !var[1])
			return (ft_strdup("$"));
		if (var[1] == '?' && (!var[2] || is_space(var[2])))
			return (ft_itoa(s->exit + g_signal));
		if (var[1] == '$' && (!var[2] || is_space(var[2])))
			return (ft_strdup("PID"));
	}
	return (ft_strdup(var));
}

int	expand_check(char *str)
{
	char	*dollar;
	int		quotes;
	int		index;

	index = 0;
	quotes = 0;
	dollar = ft_strchr(str, '$');
	if (!dollar && !ft_strchr(str, '~') && !ft_strchr(str, '*'))
		return (0);
	if (dollar && is_meta(*(dollar + 1)))
		return (0);
	while (str[index])
	{
		if (str[index] == '\'')
			quotes++;
		if (str[index] == '$')
			break ;
		index++;
	}
	if (quotes % 2 != 0)
		return (0);
	return (1);
}
