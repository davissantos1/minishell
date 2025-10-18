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

static t_lstint	*find_fd(t_lstint *lst, int fd);

void	close_redir(t_minishell *shell, t_cmd *cmd)
{
	t_lstint	*lst;
	int			std_in;
	int			std_out;

	lst = shell->lstfd;
	std_in = cmd->std_in;
	std_out = cmd->std_out;
	if (std_in != -1 && std_in != 0 && !find_fd(lst, std_in))
		close(cmd->std_in);
	if (std_out != -1 && std_out != 1 && !find_fd(lst, std_out))
		close(cmd->std_out);
}

static t_lstint	*find_fd(t_lstint *lst, int fd)
{
	if (!lst)
		return (NULL);
	while (lst && lst->value != fd)
		lst = lst->next;
	return (lst);
}
