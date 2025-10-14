/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:53:14 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/14 10:53:15 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_return(t_minishell *shell);

int	last_return(t_minishell *shell)
{
	int	exit_child;

	while (shell->lst_pid)
		exit_child = get_return(shell);
	return (exit_child);
}


static int	get_return(t_minishell *shell)
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
	return (grepper);
}
