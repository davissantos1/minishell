/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/30 12:23:23 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	temp = get_env(s->env, dollar + 1);
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

	meta = NULL;
	expand = NULL;
	if (expand_check(var))
	{
		var = remove_quotes(s, var);
		dollar = ft_strchr(var, '$');
		if (dollar)
			meta = find_meta(dollar + 1);
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
	char	*exp;
	int		index;

	index = -1;
	exp = NULL;
	if (only_quotes(str))
		return (ft_strdup(""));
	if (str[0] == '\'')
		return (ft_strtrim(str, "'"));
	if (str[0] == '\"')
		spl = ft_split(str, ' ');
	else
		spl = ft_split(str, '\"');
	while (spl[++index])
		spl[index] = expand_var(s, spl[index]);
	if (find_blank(str))
		exp = ft_reverse_split(spl, ' ');
	else
		exp = ft_merge(spl);
	if (!gc_addptr(exp, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	if (!gc_addmtx(spl, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	exp = remove_quotes(s, exp);
	return (exp);
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
		else if (dol && !is_meta(*(dol + 1)) && !is_space(*(dol + 2)))
			result[i] = expand_var(s, av[i]);
		else if (av[i][0] == '~' || dol)
			result[i] = expand_special(s, av[i]);
		else
			result[i] = ft_strdup(av[i]);
		i++;
	}
	if (!gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	result = check_wildcard(s, result);
	return (result);
}
