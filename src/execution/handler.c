/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:14:39 by vitosant          #+#    #+#             */
/*   Updated: 2025/11/01 16:00:48 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(t_minishell *shell)
{
	if (g_signal)
		shell->exit = g_signal + 128;
	g_signal = 0;
	find_heredoc(shell, shell->root);
	build_path(shell);
	if (g_signal != 2)
		executor(shell, shell->root);
	if (shell->lst_pid && g_signal != 2)
		shell->exit = last_return(shell);
	gc_free_tag(shell->gc, GC_PIDLIST);
	gc_free_tag(shell->gc, GC_FDLIST);
	gc_free_tag(shell->gc, GC_PATHS);
	shell->paths = NULL;
	g_signal = 0;
}
