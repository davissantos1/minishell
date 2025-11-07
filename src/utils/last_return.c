/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:53:14 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/07 12:33:57 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_return(t_minishell *shell);
static int	kill_process(t_minishell *shell);

static void	generic_handle(int sig)
{
	g_signal = (volatile sig_atomic_t) sig;
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", 1);
	write(1, "\n", 1);
}

int	last_return(t_minishell *shell)
{
	int			exit_child;

	signal(SIGINT, generic_handle);
	signal(SIGQUIT, generic_handle);
	while (shell->lst_pid)
	{
		exit_child = get_return(shell);
		if (g_signal != 0)
			exit_child = kill_process(shell);
	}
	g_signal = 0;
	register_parent_signals();
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

static int	kill_process(t_minishell *shell)
{		
	while (shell->lst_pid)
	{
		if (!shell->lst_pid->is_builtin)
		{
			kill(shell->lst_pid->pid, g_signal);
			waitpid(shell->lst_pid->pid, NULL, 0);
		}
		shell->lst_pid = shell->lst_pid->next;
	}
	return (g_signal + 128);
}
