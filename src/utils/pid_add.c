/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:02:26 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/27 10:08:13 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pid_add(t_minishell *shell, pid_t pid, char is_builtin, int rbuiltin)
{
	t_lstpid	*node;
	t_lstpid	*lst;

	lst = shell->lst_pid;
	node = gc_calloc(sizeof(t_lstpid), shell->gc, GC_PIDLIST);
	if (!node)
		exit_code(shell, errno);
	node->is_builtin = is_builtin;
	node->rbuiltin = rbuiltin;
	node->pid = pid;
	if (!lst)
		shell->lst_pid = node;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = node;
	}
}
