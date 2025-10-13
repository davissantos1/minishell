/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:02:26 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/11 12:07:08 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pid_add(t_minishell *shell, pid_t pid, char is_builtin, int rbuiltin)
{
	t_lstpid	*node;
	t_lstpid	*lst;

	node = gc_calloc(sizeof(t_lstpid), shell->gc, GC_PIDLIST);
	if (!node)
		exit_code(shell, errno);
	node->pid = pid;
	lst = shell->lst_pid;
	node->is_builtin = is_builtin;
	node->rbuiltin = rbuiltin;
	if (!lst)
		shell->lst_pid = node;
	else
	{
		node->next = shell->lst_pid;
		shell->lst_pid = node;
	}
}

int	get_return(t_minishell *shell)
{
	t_lstpid	*lst;
	int			grepper;

	grepper = 0;
	lst = shell->lst_pid;
	shell->lst_pid = lst->next;
	if (lst->is_builtin)
		grepper = lst->rbuiltin;
	else
		waitpid(lst->pid, &grepper, 0);
	grepper = (grepper & 0xFF00) >> 8;
	gc_delptr(lst, shell->gc, GC_PIDLIST);
	return (grepper);
}
