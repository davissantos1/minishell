/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:35:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/10/23 17:16:17 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_mixed_str(t_minishell *s, char **spl, int i, char c)
{
	char	**strs;
	char	*pos;

	pos = ft_strchr(spl[i], c);
	strs = ft_break(spl[i], (int)(pos - spl[i]));
	if ((!gc_addmtx(strs, s->gc, GC_TOKEN))
		exit_code(s, EXIT_FAILURE);
	if (!strs)
		exit_code(s, EXIT_FAILURE);
	if (spl[i][0] == c)
		strs[1] = get_env(s, strs[0]);
	else
		strs[0] = get_env(s, strs[0]);
	return (ft_strjoin(strs[0], strs[1]));
}

void	expand_mixed_wildcard(t_minishelll *s, char ***spl, int i)
{
	char	*dol;
	char	*var;
	char	*wild;
	char	**strs;

	dol = ft_strchr((*spl)[i], '$');
	wild = ft_strchr((*spl)[i], '*');
	strs = ft_break((*spl)[i], (int)(wild - (*spl)[i]);
	var = get_env(s, dol
	if (!strs)
		exit_code(s, EXIT_FAILURE);
	if (spl[i][0] == '*')
		strs[1] = get_env(s, strs[0]);
	else
		strs[0] = get_env(s, strs[0]);
	return (ft_strjoin(strs[0], strs[1]));
}
