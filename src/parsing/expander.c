/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/29 00:01:46 by dasimoes         ###   ########.fr       */
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

static char	*expand_var_aux(t_minishell *s, char *var, char *dollar, char *meta)
{
	char	*expand;
	char	*preffix;
	char	*suffix;
	char	*temp;

	preffix = ft_substr(var, 0, dollar - var);
	suffix = ft_substr(var, meta - var, var + ft_strlen(var) - meta);
	if (meta)
		*meta = '\0';
	temp = get_env(s, dollar + 1);
	if (!temp)
		temp = ft_strdup("");
	else
		temp = ft_strdup(temp);
	expand = ft_strjoin(preffix, temp);
	free(temp);
	temp = expand;
	expand = ft_strjoin(expand, suffix);
	free(temp);
	free(preffix);
	free(suffix);
	return (expand);
}

static char	*expand_var(t_minishell *s, char *var)
{
	char	*expand;
	char	*dollar;
	char	*meta;

	expand = NULL;
	if (expand_check(var))
	{
		var = remove_quotes(s, var);
		dollar = ft_strchr(var, '$');
		meta = find_break(dollar + 1);
		expand = expand_var_aux(s, var, dollar, meta);
		if (!gc_addptr(expand, s->gc, GC_AST))
			exit_code(s, EXIT_FAILURE);
		return (expand);
	}
	return (var);
}

static char	*expand_quotes(t_minishell *s, char *str)
{
	char	**spl;
	char	*res;
	char	*tmp;
	int	i;

	i = 0;
	spl = ft_split(str, '\"');
	if (!gc_addmtx(spl, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	while (spl[i])
	{
		tmp = NULL;
		if (ft_strchr(spl[i], '$'))
			tmp = expand_var(s, spl[i]);
		if (tmp)
			spl[i] = tmp;
		i++;
	}
	if (*spl)
		res = ft_merge(spl);
	if (!gc_addptr(res, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	res = remove_quotes(s, res);
	return (res);
}

char	**expand_argv(t_minishell *s, char **av)
{
	char	**result;
	char	*dol;
	int		i;

	i = 0;
	result = ft_calloc(sizeof(char *), (ft_mtxlen(av) + 1));
	if (!result)
		exit_code(s, EXIT_FAILURE);
	while (av[i])
	{
		dol = ft_strchr(av[i], '$');
		if (ft_strchr(av[i], '\"') || ft_strchr(av[i], '\''))
			result[i] = expand_quotes(s, av[i]);
		else if (dol && !is_meta(*(dol + 1)))
			result[i] = expand_var(s, av[i]);
		else if (av[i][0] == '~')
			result[i] = expand_tilde(s, av[i]);
		else
			result[i] = ft_strdup(av[i]);
		i++;
	}
	if (!gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	result = check_wildcard(s, result);
	return (result);
}
