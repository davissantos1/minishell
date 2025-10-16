/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_pipefd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:59:30 by vitosant          #+#    #+#             */
/*   Updated: 2025/10/15 14:57:36 by vitosant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub_add_fdlst(t_minishell *shell, int fd, t_subshell *sub);

void set_sub_node(t_minishell *shell, t_subshell *sub, int *fd, char flag)
{
	if (flag == STDIN_FD)
		sub->std_in = fd[0];
	else
		sub->std_out = fd[1];
	sub_add_fdlst(shell, fd[0], sub);
	sub_add_fdlst(shell, fd[1], sub);
}

static void	sub_add_fdlst(t_minishell *shell, int fd, t_subshell *sub)
{
	t_lstint	*node;

	node = gc_calloc(sizeof(t_lstint), shell->gc, GC_FDLIST);
	if (!node)
		exit_code(shell, errno);
	node->value = fd;
	node->next = sub->lst_fds;
	sub->lst_fds = node;
}
