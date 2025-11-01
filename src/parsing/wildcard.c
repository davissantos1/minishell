/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:04:28 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/31 17:24:26 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*wild_aux(t_minishell *s, char *str)
{
	static struct dirent	*cur;
	static	DIR 			*dir;
	char					*wild;
	char					*name;

	errno = 0;
	wild = NULL;
	if (!dir)
		dir = opendir(getenv("PWD"));
	if (!dir && errno)
		exit_code(s, EXIT_FAILURE);
	if (cur)
		cur = readdir(dir);
	if (!cur && errno)
		exit_code(s, EXIT_FAILURE);
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
	char	**res;
	int		index;
	int		size;

	index = 0;
	size = dir_len(getenv("PWD"));
	res = gc_calloc(size + 1, s->gc, GC_TOKEN);
	if (!res)
		exit_code(s, EXIT_FAILURE);
	while (index < size)
	{
		res[index] = wild_aux(s, str);
		index++;
	}
	return (res);
}

void	handle_wildcard(t_minishell *s, char ***result, int pos)
{
	char	**res;

	res = expand_wildcard(s, (*result)[pos]);
	*result = ft_mtxinsert(*result, res, pos);
	if (!gc_addmtx(*result, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
}
