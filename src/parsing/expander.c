/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:32:55 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/09 20:30:32 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_quotes(t_minishell *s, char *str)
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
	if (!gc_addmtx(spl, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	while (spl[++index])
		spl[index] = expand_var(s, spl[index]);
	if (str[0] == '\"')
		exp = ft_reverse_split(spl, ' ');
	else
		exp = ft_merge(spl);
	if (!gc_addptr(exp, s->gc, GC_TOKEN))
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
		else if (ft_strchr(cur->file, '~'))
			cur->file = expand_tilde(s, cur->file);
		else
			cur->file = ft_strdup(cur->file);
		if (!cur->file || !gc_addptr(cur->file, s->gc, GC_AST))
			exit_code(s, errno);
		cur = cur->next;
	}
}

char	*expand_line(t_minishell *s, char *line)
{
	char	*result;
	char	*dol;

	result = gc_calloc((ft_strlen(line) + 1), s->gc, GC_AST);
	if (!result)
		exit_code(s, EXIT_FAILURE);
	if (!line)
		return (result);
	dol = ft_strchr(line, '$');
	if (dol)
		result = expand_var(s, line);
	else
		result = ft_strdup(line);
	if (!gc_addptr(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (result);
}

char	**expand_argv(t_minishell *s, char **av)
{
	char	**result;
	char	*dol;
	int		i;

	i = 0;
	result = ft_calloc(sizeof(char *), (ft_mtxlen(av) + 2));
	while (av[i] && result)
	{
		dol = ft_strchr(av[i], '$');
		if (ft_strchr(av[i], '\"') || ft_strchr(av[i], '\''))
			result[i] = expand_quotes(s, av[i]);
		else if (dol)
			result[i] = expand_var(s, av[i]);
		else if (ft_strchr(av[i], '~'))
			result[i] = expand_tilde(s, av[i]);
		else
			result[i] = ft_strdup(av[i]);
		if (ft_strchr(av[i], '*'))
			handle_wildcard(s, &result, i);
		i++;
	}
	if (!result || !gc_addmtx(result, s->gc, GC_AST))
		exit_code(s, EXIT_FAILURE);
	return (result);
}
