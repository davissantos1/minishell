/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:04:28 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/29 17:47:47 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*wild_aux(char *str, struct dirent *cur)
{
	char	*wild;
	char	*name;

	errno = 0;
	wild = NULL;
	name = (char *)cur->d_name;
	if (check_wildcard_char(str))
	{
		if (name[0] != '.')
			wild = ft_strdup(name);
	}
	else if (check_wildcard_str(str, cur->d_name))
		wild = ft_strdup(name);
	if (!wild)
		return (ft_strdup(""));
	return (wild);
}

static char	**expand_wildcard(t_minishell *s, char *str)
{
	char			**res;
	DIR 			*dir;
	struct dirent	*cur;
	int				index;

	index = 0;
	errno = 0;
	dir = opendir(getenv("PWD"));
	res = gc_calloc(dir_len(getenv("PWD")), s->gc, GC_TOKEN);
	if (!res)
		exit_code(s, EXIT_FAILURE);
	if (!dir && errno)
		exit_code(s, EXIT_FAILURE);
	cur = readdir(dir);
	if (!cur && errno)
		exit_code(s, EXIT_FAILURE);
	while (cur)
	{
		res[index] = wild_aux(str, cur);
		index++;
		cur = readdir(dir);
		if (!cur && errno)
			exit_code(s, EXIT_FAILURE);
	}
	return (res);
}

char	**check_wildcard(t_minishell *s, char **result)
{
	int		index;
	char	**res;
	char	**tmp;
	char	**exp;

	index = 0;
	exp = NULL;
	while (result[index])
	{
		if (ft_strchr(result[index], '*'))
		{
			res = expand_wildcard(s, result[index]);
			tmp = ft_mtxndup(result, index - 1);
			exp = ft_mtxjoin(tmp, res);
			tmp = ft_mtxfree(tmp);
			res = ft_mtxfree(res);
			tmp = exp;
			res = ft_mtxdup(result + index);
			exp = ft_mtxjoin(exp, res);
			tmp = ft_mtxfree(tmp);
			res = ft_mtxfree(res);
		}
		index++;
	}
	if (!exp)
		return (result);
	if (!gc_addmtx(exp, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	return (exp);
}
