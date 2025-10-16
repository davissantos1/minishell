/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_close_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:23:02 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 13:52:41 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lstint	*find_fd(t_subshell *sub, int fd);

void	sub_close_redir(t_subshell *sub)
{
	if (sub->std_in != -1 && sub->std_in != 0 && !find_fd(sub, sub->std_in))
		close(sub->std_in);
	if (sub->std_out != -1 && sub->std_out != 1 && !find_fd(sub, sub->std_out))
		close(sub->std_out);
}

static t_lstint	*find_fd(t_subshell *sub, int fd)
{
	t_lstint	*lst;

	lst = sub->lst_fds;
	if (!lst)
		return (NULL);
	while (lst && lst->value != fd)
		lst = lst->next;
	return (lst);
}
