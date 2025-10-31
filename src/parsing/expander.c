/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/31 11:30:42 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_var_aux(t_minishell *s, char *var, char *dollar, char *end)
{
	char	*expand;
	char	*preffix;
	char	*suffix;
	char	*temp;

	preffix = ft_substr(var, 0, dollar - var);
	suffix = ft_substr(var, end - var, var + ft_strlen(var) - end);
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

static char	*expand_var(t_minishell *s, char *var)
{
	char	*expand;
	char	*dollar;
	char	*end;

	end = NULL;
	expand = NULL;
	if (expand_check(var))
	{
		var = remove_quotes(s, var);
		dollar = ft_strchr(var, '$');
		if (dollar)
			end = find_break(dollar + 1);
		expand = expand_var_aux(s, var, dollar, end);
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
	if (expand_check_quotes(str))
		return (remove_quotes(s, str));
	if (str[0] == '\"')
		spl = ft_split(str, ' ');
	else
		spl = ft_split(str, '\"');
	while (spl[++index])
		spl[index] = expand_var(s, spl[index]);
	if (str[0] == '\"')
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

void	expand_redirect(t_minishell *s, t_redir *redir)
{
	t_redir	*cur;
	char	*dol;

	cur = redir;
	while (cur)
	{
		dol = ft_strchr(cur->file, '$');
		if (ft_strchr(cur->file, '\"') || ft_strchr(cur->file, '\''))
			cur->file = expand_quotes(s, cur->file);
		else if (dol)
			cur->file = expand_var(s, cur->file);
		else if (ft_strchr(cur->file, '*'))
			handle_wildcard(s, NULL, 0);
		else
			cur->file = ft_strdup(cur->file);
		cur = cur->next;
	}
}

char	**expand_argv(t_minishell *s, char **av)
{
	char	**result;
	char	*dol;
	int		i;

	i = 0;
	result = ft_calloc(sizeof(char *), (ft_mtxlen(av) + 2));
	if (!result)
		exit_code(s, EXIT_FAILURE);
	while (av[i])
	{
		dol = ft_strchr(av[i], '$');
		if (ft_strchr(av[i], '\"') || ft_strchr(av[i], '\''))
			result[i] = expand_quotes(s, av[i]);
		else if (dol)
			result[i] = expand_var(s, av[i]);
		else if (ft_strchr(av[i], '*'))
			handle_wildcard(s, &result, i);
		else
			result[i] = ft_strdup(av[i]);
		i++;
	}
	if (!gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (result);
}
