/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:33:19 by vitosant          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/11/11 18:11:08 by dasimoes         ###   ########.fr       */
=======
/*   Updated: 2025/11/11 17:03:35 by vitosant         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*wildcard_flow(char *name, char *path)
{
	if (!ft_strcmp(path, "."))
	{
		if (name[0] == '.')
			return (ft_strdup(name));
	}
	else if (!ft_strcmp(path, ".."))
		return (path);
	else if (name[0] != '.')
		return (ft_strjoin(path, name));
	return (NULL);
}

static char	*expand_wildcard_aux(t_minishell *s, char *str, char *name)
{
	char	*wild;
	char	*path;

	wild = NULL;
	path = get_wildcard_path(s, str);
	if (check_wildcard_char(str + ft_strlen(path)))
		wild = wildcard_flow(name, path);
	else if (check_wildcard_str(str + ft_strlen(path), name))
		wild = ft_strjoin(path, name);
	if (!wild)
		return (NULL);
	if (!gc_addptr(wild, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	return (wild);
}

static char	**expand_wildcard(t_minishell *s, char *str)
{
	static struct dirent	*cur;
	static DIR				*dir;
	char					**res;
	int						index;

	errno = 0;
	index = 0;
	res = gc_calloc((dlen(gdir(s, str)) + 1) * sizeof(char *), s->gc, GC_TOKEN);
	dir = opendir(gdir(s, str));
	if (!dir)
		return (NULL);
	while (1)
	{
		cur = readdir(dir);
		if (!cur)
			break ;
		res[index] = expand_wildcard_aux(s, str, (char *)cur->d_name);
		if (res[index])
			index++;
	}
	closedir(dir);
	return (res);
}

int	maybe_wildcard(char *str)
{
	char	quotes;
	int		open;
	int		i;

	i = -1;
	open = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !open)
			is_open(&open, &quotes, str[i]);
		else if (open && str[i] == quotes)
			open = 0;
		if (!open && str[i] == '*')
			return (1);
	}
	return (0);
}

void	handle_wildcard(t_minishell *s, char ***result, int pos)
{
	char	**res;

	res = expand_wildcard(s, (*result)[pos]);
	if (!gc_addptr(*result, s->gc, GC_TOKEN)
		|| !gc_addptr(result[0][pos], s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	if (!res)
	{
		error_code(s, EXIT_FAILURE);
		return ;
	}
	sort_table(res, ALPHA_ORDER);
	if (!gc_addmtx(res, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	if (res[0])
		(*result)[pos] = ft_strdup("");
	if (!gc_addmtx(*result, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	*result = ft_mtxinsert(*result, res, pos);
	if (!gc_addmtx(*result, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
}
