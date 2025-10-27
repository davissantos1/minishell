/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/27 11:40:50 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_check(char *str)
{
	int	quotes;
	int	index;

	index = 0;
	quotes = 0;
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

static char	*expand_var(t_minishell *s, char *var)
{
	char	*env_var;

	if (expand_check(var))
	{
		env_var = remove_quotes(s, var);
		env_var = get_env(s, var + 1);
		if (!env_var)
			return (ft_strdup(""));
		return (ft_strdup(env_var));
	}
	return (var);
}

static char	*expand_quotes(t_minishell *s, char *str)
{
	char	**spl;
	char	*res;
	int	i;

	i = 0;
	spl = ft_split(str, '\"');
	if (!gc_addmtx(spl, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	while (spl[i])
	{
		if (ft_strchr(spl[i], '$'))
			spl[i] = expand_var(s, spl[i]);
		i++;
	}
	if (spl)
		res = ft_merge(spl);
	else
		res = str;
	if (!gc_addptr(res, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	res = remove_quotes(s, res);
	return (res);
}

char	**expand_argv(t_minishell *s, char **av)
{
	char	**result;
	int		index;

	index = 0;
	result = ft_calloc(sizeof(char *), (ft_mtxlen(av) + 1));
	if (!result)
		exit_code(s, EXIT_FAILURE);
	while (av[index])
	{	
		if (ft_strchr(av[index], '\"') || ft_strchr(av[index], '\''))
			result[index] = expand_quotes(s, av[index]);
		else if (av[index][0] == '$' && av[index][1])
			result[index] = expand_var(s, av[index]);
		else if (av[index][0] == '~' && !av[index][1])
			result[index] = ft_strdup(getenv("HOME"));
		else
			result[index] = ft_strdup(av[index]);
		index++;
	}
	if (!gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	result = check_wildcard(s, result);
	return (result);
}
