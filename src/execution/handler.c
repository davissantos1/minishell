/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:14:39 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/07 14:15:37 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc(int sig)
{
	g_signal = (volatile sig_atomic_t) sig;
	rl_done = 1;
	write(1, "\n", 1);
	write(1, "\033[091mMinishell$ \033[0m", 21);
}

void	handler(t_minishell *shell)
{
	if (g_signal)
		shell->exit = g_signal + 128;
	g_signal = 0;
	signal(SIGINT, sigint_heredoc);
	find_heredoc(shell, shell->root);
	register_parent_signals();
	build_path(shell);
	if (g_signal != 2)
		executor(shell, shell->root);
	if (shell->lst_pid && g_signal != 2)
		shell->exit = last_return(shell);
	gc_free_tag(shell->gc, GC_PIDLIST);
	gc_free_tag(shell->gc, GC_FDLIST);
	gc_free_tag(shell->gc, GC_PATHS);
	shell->paths = NULL;
}
