/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:11:19 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/11 18:41:10 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(t_minishell *s, char *var, char *dollar, char *end)
{
	char	*expand;
	char	*preffix;
	char	*suffix;
	char	*temp;

	preffix = ft_substr(var, 0, dollar - var);
	if (!end || !*end)
		suffix = ft_strdup("");
	else
	{
		suffix = ft_substr(var, end - var, var + ft_strlen(var) - end);
		*end = '\0';
	}
	temp = expand_special(s, dollar);
	expand = ft_strjoin(preffix, temp);
	free(temp);
	temp = expand;
	expand = ft_strjoin(expand, suffix);
	free(temp);
	free(preffix);
	free(suffix);
	return (expand);
}

static char	**get_sub(t_minishell *s, char *var)
{
	char	**res;
	char	*end;
	int		start;
	int		i;

	i = -1;
	res = gc_calloc((ft_strlen(var) + 1) * sizeof(char *), s->gc, GC_AST);
	if (!res)
		exit_code(s, EXIT_FAILURE);
	end = find_break(var);
	start = find_index(var, var);
	while (*end)
	{
		res[++i] = ft_substr(var, start, find_index(var, end) - start + 1);
		start = find_index(var, end + 1);
		end = find_break(end + 1);
	}
	res[++i] = ft_substr(var, start, find_index(var, end) - start + 1);
	if (!gc_addmtx(res, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (res);
}

char	*expand_var(t_minishell *s, char *var, int quotes)
{
	char	*dollar;
	char	**res;
	char	*exp;
	int		i;

	i = -1;
	if (!maybe_expand(var))
		return (remove_quotes(s, var));
	if (quotes)
		var = remove_quotes(s, var);
	res = get_sub(s, var);
	while (res[++i])
	{
		dollar = ft_strchr(res[i], '$');
		if (var[0] == '\'' && var[ft_strlen(var) - 1] == '\'' && dollar)
			res[i] = expand(s, res[i], dollar, ft_strchr(res[i] + 1, '\''));
		else if (dollar)
			res[i] = expand(s, res[i], res[i], find_meta(res[i]));
		if (!gc_addptr(res[i], s->gc, GC_AST))
			exit_code(s, EXIT_FAILURE);
	}
	exp = ft_merge(res);
	if (!gc_addptr(exp, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (exp);
}
