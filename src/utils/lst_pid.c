/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:02:26 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/07 11:54:18 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pid_add(t_minishell *shell, pid_t pid)
{
	t_lstpid	*node;
	t_lstpid	*lst;

	node = gc_calloc(sizeof(t_lstpid), shell->gc, GC_CUSTOM2);
	if (!node)
		exit_code(shell, errno);
	node->pid = pid;
	lst = shell->lst_pid;
	if (!lst)
		shell->lst_pid = node;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = node;
	}
}

int	get_return(t_minishell *shell)
{
	t_lstpid	*lst;
	int			grepper;

	lst = shell->lst_pid;
	grepper = 0;
	waitpid(lst->pid, &grepper, 0);
	gc_delptr(lst, shell->gc, GC_CUSTOM2);
	grepper = (grepper & 0xFF00) >> 8;
	return (grepper);
}
