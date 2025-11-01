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

static char	*wild_aux(t_minishell *s, char *str, char *name)
{
	char	*wild;

	wild = NULL;
	if (check_wildcard_char(str))
	{
		if (name[0] != '.')
			wild = ft_strdup(name);
		else
			wild = ft_strdup("");
	}
	else if (check_wildcard_str(str, name))
		wild = ft_strdup(name);
	else
		wild = ft_strdup("");
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
	res = gc_calloc((dir_len(".") + 1) * sizeof(char *), s->gc, GC_TOKEN);
	if (!res)
		exit_code(s, EXIT_FAILURE);
	dir = opendir(getenv("PWD"));
	if (!dir && errno)
		exit_code(s, EXIT_FAILURE);
	while (1)
	{
		cur = readdir(dir);
		if (!cur)
			break ;
		res[index] = wild_aux(s, str, (char *)cur->d_name);
		index++;
	}
	closedir(dir);
	if (errno)
		exit_code(s, EXIT_FAILURE);
	sort_table(res);
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
