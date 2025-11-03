/* ************************************************************************** */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:04:28 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/01 20:06:32 by dasimoes         ###   ########.fr       */
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
	static	DIR 			*dir;
	char					**res;
	int						index;

	index = 0;
	errno = 0;
	res = gc_calloc((dlen(gdir(s, str)) + 1) * sizeof(char *), s->gc, GC_TOKEN);
	if (!res)
		exit_code(s, EXIT_FAILURE);
	dir = opendir(gdir(s, str));
	if (!dir && errno)
		exit_code(s, EXIT_FAILURE);
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
	if (errno)
		exit_code(s, EXIT_FAILURE);
	return (res);
}

void	handle_wildcard(t_minishell *s, char ***result, int pos)
{
	char	**res;

	res = expand_wildcard(s, (*result)[pos]);
	sort_table(res);
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
