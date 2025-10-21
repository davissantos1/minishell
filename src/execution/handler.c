/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 08:14:39 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/20 16:38:41 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(t_minishell *shell)
{
	find_heredoc(shell, shell->root);
	build_path(shell);
	if (shell->exit != 130)
		executor(shell, shell->root);
	if (shell->lst_pid)
		shell->exit = last_return(shell);
	gc_free_tag(shell->gc, GC_PIDLIST);
	gc_free_tag(shell->gc, GC_FDLIST);
	gc_free_tag(shell->gc, GC_PATHS);
	shell->paths = NULL;
}
