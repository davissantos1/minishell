/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:04:25 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 10:26:27 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_endbar(t_minishell *shell, char **paths);

void	build_path(t_minishell *shell)
{
	char	*genv;
	char	**paths;

	genv = getenv("PATH");
	if (!genv)
		return ;
	paths = ft_split(genv, ':');
	put_endbar(shell, paths);
	if (paths)
	{
		if (!gc_addmtx(paths,shell->gc, GC_PATHS))
			exit_code(shell, errno);
		shell->paths = paths;
	}
}

static void	put_endbar(t_minishell *shell, char **paths)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			exit_code(shell, errno);
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
}
