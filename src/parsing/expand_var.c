/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:11:19 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/07 17:12:43 by dasimoes         ###   ########.fr       */
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

char	*expand_var(t_minishell *s, char *var)
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
