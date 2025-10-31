/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:35:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/31 11:31:35 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_expand(char *str)
{
	char	*dollar;
	char	after;

	dollar = ft_strchr(str, '$');
	after = *(dollar + 1);
	if (after == '?')
		return (1);
	if (after == '$')
		return (1);
	if (ft_isdigit(after))
		return (1);
	if (after)
		return (1);
	return (0);
}

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
		env_var = get_env(s->env, "OLDPWD");
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
	}
	if (var[1] == '+' && (!var[2] || is_space(var[2])))
	{
		env_var = get_env(s->env, "PWD");
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
	}
	return (ft_strdup(var));
}

char	*expand_special(t_minishell *s, char *var)
{
	char	*env_var;
	char	*tmp;

	if (var[0] == '~')
		return (expand_tilde(s, var));
	if (var[0] == '$')
	{
		if (is_space(var[1]) || !var[1])
			return (ft_strdup("$"));
		if (var[1] == '?') 
			return (ft_itoa(s->exit + g_signal));
		if (var[1] == '$')
			return (ft_strdup("PID"));
		if (var[1] == '0')
			return (ft_strdup(s->name));
		env_var = get_env(s->env, &var[1]);
		tmp = ft_substr(var, 1, 1);
		if (ft_isdigit(var[1]))
			env_var = get_env(s->env, tmp);
		free(tmp);
		if (env_var)
			return (ft_strdup(env_var));
		return (ft_strdup(""));
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
	if (!dollar && str[0] == '\"')
		return (0);
	if (dollar && !dollar_expand(str))
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

int	expand_check_quotes(char *str)
{
	char	*dollar;

	dollar = ft_strchr(str, '$');
	if (str[0] == '\"' && !dollar)
		return (1);
	if (str[0] == '\"' && dollar && is_space(*(dollar + 1)))
		return (1);
	if (str[0] == '\'')
		return (1);
	return (0);
}
