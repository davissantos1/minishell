/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:51:19 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 10:18:40 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_bin(t_minishell *shell, char *command);

void	find_path(t_minishell *shell, t_cmd *cmd)
{
	char *tmp;

	if (!shell->paths || ft_strchr(cmd->argv[0], '/'))
		return ;
	tmp = find_bin(shell, cmd->argv[0]);
	if (tmp == cmd->argv[0])
		return ;
	if (!gc_addptr(tmp, shell->gc, GC_PATHS))
		exit_code(shell, errno);
	cmd->argv[0] = tmp;
}

static char	*find_bin(t_minishell *shell, char *command)
{
	size_t	i;
	char	*fcommand;

	i = 0;
	while (shell->paths[i])
	{
		fcommand = ft_strjoin(shell->paths[i], command);
		if (!fcommand)
			exit_code(shell, errno);
		if (!access(fcommand, F_OK))
			return (fcommand);
		free(fcommand);
		i++;
	}
	return (command);
}
