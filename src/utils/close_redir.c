/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:40:00 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/11 13:44:47 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lstint	*find_fd(t_cmd *cmd, int fd);

void	close_redir(t_cmd *cmd)
{
	if (cmd->std_in != -1 && cmd->std_in != 0 && !find_fd(cmd, cmd->std_in))
		close(cmd->std_in);
	if (cmd->std_out != -1 && cmd->std_out != 1 && !find_fd(cmd, cmd->std_out))
		close(cmd->std_out);
}

static t_lstint	*find_fd(t_cmd *cmd, int fd)
{
	t_lstint	*lst;

	lst = cmd->lst_fds;
	if (!lst)
		return (NULL);
	while (lst && lst->value != fd)
		lst = lst->next;
	return (lst);
}
